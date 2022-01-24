
const int MOD = 998244353;
struct PrimeField {
    int r;

    PrimeField(): r(0) {}
    PrimeField(ll x) {
        r = x % MOD;
        if (r < 0)
            r += MOD;
    }
    PrimeField(const PrimeField& oth): r(oth.r) {}

    PrimeField operator - () {
        return PrimeField(-r);
    }
    PrimeField& operator += (const PrimeField& oth) {
        if ((r += oth.r) >= MOD)
            r -= MOD;
        return *this;
    }
    PrimeField& operator -= (const PrimeField& oth) {
        if ((r -= oth.r) < 0)
            r += MOD;
        return *this;
    }
    PrimeField& operator *= (const PrimeField& oth) {
        r = r * (ll)oth.r % MOD;
        return *this;
    }
};
ostream& operator << (ostream& stream, const PrimeField& a) {
    return stream << a.r;
}
PrimeField operator + (const PrimeField& lhs, const PrimeField& rhs) { return PrimeField(lhs) += rhs; }
PrimeField operator - (const PrimeField& lhs, const PrimeField& rhs) { return PrimeField(lhs) -= rhs; }
PrimeField operator * (const PrimeField& lhs, const PrimeField& rhs) { return PrimeField(lhs) *= rhs; }
bool operator == (const PrimeField& lhs, const PrimeField& rhs) { return lhs.r == rhs.r; }
bool operator != (const PrimeField& lhs, const PrimeField& rhs) { return lhs.r != rhs.r; }
PrimeField bpow(PrimeField a, ll b) {
    PrimeField res = 1;
    for (; b; b >>= 1, a *= a)
        if (b & 1)
            res *= a;
    return res;
}
PrimeField inv(PrimeField a) {
    return bpow(a, MOD - 2);
}


struct PowerSeries {
    vector<PrimeField> f;

    void remove_trailing_zeroes() {
        while (!f.empty() && f.back() == 0)
            f.pop_back();
    }

    PowerSeries() {}
    PowerSeries(PrimeField x) {
        f = {x};
        remove_trailing_zeroes();
    }
    PowerSeries(vector<PrimeField> v) {
        f = v;
        remove_trailing_zeroes();
    }
    PowerSeries(const PowerSeries& oth): f(vector<PrimeField>(oth.f)) {}

    PowerSeries& trim(int n) {
        while ((int)f.size() > n)
            f.pop_back();
        return *this;
    }

    PrimeField coef(int i) {
        return i < (int)f.size() ? f[i] : 0;
    }
    PrimeField& operator [] (int i) {
        return f[i];
    }

    PowerSeries& operator += (const PowerSeries& oth) {
        if (f.size() < oth.f.size())
            f.resize(oth.f.size());
        for (int i = 0; i < (int)oth.f.size(); ++i)
            f[i] += oth.f[i];
        remove_trailing_zeroes();
        return *this;
    }
    PowerSeries& operator -= (const PowerSeries& oth) {
        if (f.size() < oth.f.size())
            f.resize(oth.f.size());
        for (int i = 0; i < (int)oth.f.size(); ++i)
            f[i] -= oth.f[i];
        remove_trailing_zeroes();
        return *this;
    }
    PowerSeries operator - () {
        auto res = PowerSeries(*this);
        for (auto& x : res.f) x = -x;
        return res;
    }
    PowerSeries& operator *= (PrimeField k) {
        if (k == 0) {
            f.clear();
            return *this;
        }
        for (auto& x : f)
            x *= k;
        return *this;
    }
};
const PowerSeries UNIT(1);
PowerSeries operator + (const PowerSeries& lhs, const PowerSeries& rhs) { return PowerSeries(lhs) += rhs; }
PowerSeries operator - (const PowerSeries& lhs, const PowerSeries& rhs) { return PowerSeries(lhs) -= rhs; }
PowerSeries operator * (const PowerSeries& lhs, PrimeField k) { return PowerSeries(lhs) *= k; }
PowerSeries operator * (PrimeField k, const PowerSeries& lhs) { return PowerSeries(lhs) *= k; }
ostream& operator << (ostream& stream, const PowerSeries& A) {
    return stream << A.f;
}

namespace fft {
    const int logN = 19;
    const int N = 1 << logN;
    PrimeField invN;
    PrimeField w[N];
    int brev[N];

    pii getSz(int need) {
        int k = 0, n = 1;
        for (; n < need; n *= 2) ++k;
        return {k, n};
    }

    void init() {
        w[0] = 1;
        w[1] = bpow(5, (MOD - 1) / N);
        for (int i = 2; i < N; ++i) {
            w[i] = w[i - 1] * w[1];
        }
        for (int i = 1; i < N; ++i)
            brev[i] = (brev[i >> 1] >> 1) | ((i & 1) << (logN - 1));
        invN = inv(N);
    }

    void fft(vector<PrimeField>& a, int k, int n) {
        for (int i = 0; i < n; ++i) {
            int j = brev[i] >> (logN - k);
            if (i < j)
                swap(a[i], a[j]);
        }
        for (int l = 1, h = 0; l < n; l *= 2, ++h) {
            int logStep = logN - h - 1;
            for (int i = 0; i < n; i += 2 * l) {
                for (int j = 0; j < l; ++j) {
                    auto u = a[i + j];
                    auto v = a[i + j + l] * w[j << logStep];
                    a[i + j] = u + v;
                    a[i + j + l] = u - v;
                }
            }
        }
    }

    void reverse_fft(vector<PrimeField>& a, int k, int n) {
        fft(a, k, n);
        reverse(a.begin() + 1, a.end());
        PrimeField inv_n = inv(n);
        for (auto& x : a)
            x *= inv_n;
    }

    vector<PrimeField> mul(vector<PrimeField> a, vector<PrimeField> b) {
        if (a.empty() || b.empty()) return {};
        int need = a.size() + b.size() - 1;
        auto [k, n] = getSz(need);
        assert(n <= N);
        a.resize(n);
        b.resize(n);
        fft(a, k, n);
        fft(b, k, n);
        for (int i = 0; i < n; ++i)
            a[i] *= b[i];
        reverse_fft(a, k, n);
        return a;
    }

    vector<PrimeField> square(vector<PrimeField> a) {
        if (a.empty()) return {};
        int need = 2 * a.size() - 1;
        auto [k, n] = getSz(need);
        assert(n <= N);
        a.resize(n);
        fft(a, k, n);
        for (int i = 0; i < n; ++i)
            a[i] *= a[i];
        reverse_fft(a, k, n);
        return a;
    }

    vector<PrimeField> squareFirstTimesSecond(vector<PrimeField> a, vector<PrimeField> b) {
        if (a.empty() || b.empty()) return {};
        int need = 2 * a.size() + b.size() - 2;
        auto [k, n] = getSz(need);
        assert(n <= N);
        a.resize(n);
        b.resize(n);
        fft(a, k, n);
        fft(b, k, n);
        for (int i = 0; i < n; ++i)
            a[i] *= a[i] * b[i];
        reverse_fft(a, k, n);
        return a;
    }
}
PowerSeries operator * (const PowerSeries& A, const PowerSeries& B) {
    return PowerSeries(fft::mul(A.f, B.f));
}

PowerSeries square(PowerSeries A) {
    return PowerSeries(fft::square(A.f));
}

PowerSeries squareFirstTimesSecond(PowerSeries A, PowerSeries B) {
    return PowerSeries(fft::squareFirstTimesSecond(A.f, B.f));
}

PowerSeries inv(PowerSeries A, int sz) {
    assert(A[0] != 0);
    PowerSeries B = inv(A[0]);
    for (int n = 1; n < sz; n *= 2) {
        auto trimmedA = A;
        trimmedA.trim(2 * n);
        B = 2 * B - squareFirstTimesSecond(B, trimmedA).trim(2 * n);
    } 
    return B;
}

PowerSeries sqrt_first_unit(PowerSeries A, int sz) { // A[0] == 1
    assert(A[0] == 1);
    PowerSeries B(1);
    for (int n = 1; n < sz; n *= 2) {
        auto trimmedA = A;
        trimmedA.trim(2 * n);
        B = (MOD + 1) / 2 * (B + trimmedA * inv(B, 2 * n)).trim(2 * n);
    }
    return B;
}

void __precalc() {
    fft::init();
}

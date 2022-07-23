import os

cpu_count = 16
for cpu_id in range(cpu_count):
    os.system("sudo cpufreq-set -c {cpu_id} -g performance".format(cpu_id=cpu_id))

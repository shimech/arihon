import os
import sys
import glob
import itertools
import time


INPUT_DIR = sys.argv[1]


def main():
    files = sorted(glob.glob(os.path.join(INPUT_DIR, '*.txt')))
    for f in files:
        t_start = time.perf_counter()
        ans = solve(f)
        t_end = time.perf_counter()
        print('Input file : {}'.format(f))
        print('Answer : {}'.format(ans))
        print('Time : {:.0f} msec'.format((t_end - t_start) * 1e3))
        print('###############')
    return


def solve(f):
    with open(f, mode='r') as f:
        lines = [l.strip() for l in f.readlines()]
    n, m = map(int, lines[0].split(' '))
    k = list(map(int, lines[1].split(' ')))
    candidate = list(itertools.product(k, repeat=4))
    for c in candidate:
        if sum(c) == m:
            return 'Yes'
    return 'No'


if __name__ == '__main__':
    main()

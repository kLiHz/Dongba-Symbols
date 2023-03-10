import os
import sys

if len(sys.argv) > 3:
    prefix = sys.argv[1]
    a = int(sys.argv[2])
    b = int(sys.argv[3])

    for i in range(a, b+1):
        dir = os.path.join(prefix, f'{i:04}')
        if os.path.exists(dir):
            print(f'Directory "{dir}" exists.')
        else:
            os.mkdir(dir)

else:
    print('Missing arguments.')

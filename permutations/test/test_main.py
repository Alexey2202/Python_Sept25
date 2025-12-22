import subprocess


def get_data(fname):
    with open('test/data/' + fname, 'r') as ifile:
        return [line.strip() for line in ifile.readlines()]


def run_test(line, expected):
    proc = subprocess.Popen(
        ['./a.out'], stdout=subprocess.PIPE, stdin=subprocess.PIPE)
    out = proc.communicate(input=line.encode())[0].decode().strip()
    result = ''.join(out).replace('\r', '').split('\n')
    assert expected == result


def test_1():
    run_test('1', get_data('test1.out'))


def test_2():
    run_test('2', get_data('test2.out'))


def test_3():
    run_test('3', get_data('test3.out'))


def test_4():
    run_test('4', get_data('test4.out'))

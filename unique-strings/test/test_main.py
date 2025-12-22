import subprocess
import random
import string


def run_test(lines, expected):
    proc = subprocess.Popen(
        ['./a.out'], stdout=subprocess.PIPE, stdin=subprocess.PIPE)
    out = proc.communicate(input='\n'.join(lines).encode())[0]
    assert expected == int(out)


def test_example():
    lines = '6 first second first third second second'.split()
    run_test(lines, 3)


def test_simple():
    lines = '10 ana lala lola lola lalo ana lalo lolo lalo lala'.split()
    run_test(lines, 5)


def random_word(lo=10, hi=20):
    return ''.join(
        random.choices(string.ascii_lowercase, k=random.randint(lo, hi)))


def test_random():
    random.seed(17)
    for _ in range(20):
        words = [
            random_word() for _ in range(random.randint(10**2, 10**4))] * 10
        random.shuffle(words)
        run_test([str(len(words))] + words, len(words) // 10)

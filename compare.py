# 对拍

import random, subprocess, os
from typing import TextIO

# 准备好这些文件
test_exec, ac_exec = "a.out", "ac.out"
# 输入输出文件不用在意
in_file, out_file, answer_file = "in.txt", "out.txt", "answer.txt"

# 自己写生成数据的逻辑
def generate_data(f: TextIO):
    print("data", file=f)

def run_program():
    subprocess.run([f"./{test_exec}"], stdin=open(in_file, "r"), stdout=open(out_file, "w"))
    subprocess.run([f"./{ac_exec}"], stdin=open(in_file, "r"), stdout=open(answer_file, "w"))

def check_result():
    with open(out_file, "r") as f1, open(answer_file, "r") as f2:
        out_content = f1.read()
        answer_content = f2.read()
        return out_content == answer_content

if __name__ == "__main__":
    test_times = int(8e4)
    print("checking...")
    for i in range(test_times):
        f = open(in_file, "w")
        generate_data(f)
        f.close()

        run_program()
        if check_result():
            print(f"\rTest {i + 1:06d} / {test_times:06d} passed", end="")
        else:
            print(f"\rTest {i + 1:06d} / {test_times:06d} failed", end="")
            break
    print(f"{os.linesep}Test {test_times} completed")
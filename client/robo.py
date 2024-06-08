from threading import Thread
import sys
import os
import random

lista = ['00001','00002','00003','00004','00005','00006','00007','00008','00009','00010']
thread_total = 1000

class Th(Thread):

        def __init__ (self, num):
                sys.stdout.write("Making thread number " + str(num) + "n")
                sys.stdout.flush()
                Thread.__init__(self)
                self.num = num

        def run(self):               
                os.system(f"./a.out < t-{str(self.num)}.txt")
                sys.stdout.flush()
                   

for thread_number in range (thread_total):
        
        m = random.randint(1, 10) # quantidade produto
        #m = 1

        info = f"{thread_number} "

        for i in range(m):
                
                n = random.randint(0, 9) # produto ID

                info += f"3 {lista[n]} 1 "

        info += "5 5"

        f = open(f"t-{str(thread_number)}.txt", "w")
        f.write(info)
        f.close()

for thread_number in range(thread_total):

        thread = Th(thread_number)
        thread.start()
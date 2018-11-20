
import os
import multiprocessing

class mulpro(multiprocessing.Process):
    def __init__(self,name,file):
        multiprocessing.Process.__init__(self)
        self.name = name
        self.file = file
    def run(self):
        dir = os.getcwd()
        with open(dir + self.file + ".py","r") as f:
            for line in f:
                exec(line)


def execute(file):
    prc = mulpro("proc-0",file)
    prc.start()
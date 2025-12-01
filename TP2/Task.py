import time

class Task:
    def __init__(self, identifier, size=None):
        self.identifier = identifier
        self.size = size
        self.a = 0
        self.b = 0
        self.x = 0
        self.time = 0

    def work(self):

        start = time.time()
        time.sleep(1)
        self.time = time.time() - start
        print(f"Tâche {self.identifier} traitée en {self.time:.2f} sec")
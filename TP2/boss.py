from client import QueueClient
from Task import Task
import time

class Boss(QueueClient):
    def start(self):
        for i in range(10):
            t = Task(identifier=i, size=100)
            print(f"Boss envoie la tâche {i}")
            self.task_queue.put(t)

        print("Toutes les tâches sont envoyées.")


        for i in range(10):
             res = self.result_queue.get()
             print(f"Boss a reçu le résultat de la tâche {res.identifier}")

if __name__ == '__main__':
    boss = Boss()
    boss.start()
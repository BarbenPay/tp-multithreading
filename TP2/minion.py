from client import QueueClient
from Task import Task
import time

class Minion(QueueClient):
    def start(self):
        print("Minion prêt à travailler...")
        while True:
            if not self.task_queue.empty():
                task_item = self.task_queue.get()
                
                print(f"Minion traite la tâche {task_item.identifier}")
                task_item.work()
                
                self.result_queue.put(task_item)
            else:
                time.sleep(0.5)

if __name__ == '__main__':
    minion = Minion()
    minion.start()
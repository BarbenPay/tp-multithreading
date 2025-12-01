import os
from multiprocessing.managers import BaseManager
from queue import Queue


task_queue = Queue()
result_queue = Queue()


def get_task_queue_spy():
    print("[MANAGER] -> Un client a demandé l'accès à la TASK queue")
    return task_queue

def get_result_queue_spy():
    print("[MANAGER] -> Un client a demandé l'accès à la RESULT queue")
    return result_queue

class QueueManager(BaseManager):
    pass


QueueManager.register('get_task_queue', callable=get_task_queue_spy)
QueueManager.register('get_result_queue', callable=get_result_queue_spy)

if __name__ == '__main__':
    socket_file = '/tmp/job_queue'

    if os.path.exists(socket_file):
        os.remove(socket_file)

    m = QueueManager(address=socket_file, authkey=b'secret')
    
    print("Manager démarré... En attente.")
    s = m.get_server()
    s.serve_forever()
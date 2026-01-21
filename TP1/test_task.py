import unittest
import numpy.testing as np
from task import Task


class TestTask(unittest.TestCase):
    def test_solve_ax_equals_b(self):
        my_task = Task()
        res = my_task.a @ my_task.x
        expt_res = my_task.b
        np.assert_allclose(res, expt_res)


if __name__ == "__main__":
    unittest.main()

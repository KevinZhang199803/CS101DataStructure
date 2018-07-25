from utils import io
from utils import Awards
from utils import DriverDistribution as dd
import time

init_time = time.time()
ptr = [104.0545, 30.7116]

io.filepath = "/home/kevin/ShanghaiTech/Sophomore/DS/Project/Codes/data/clusters_start.js"
start_dir = io.readin()
io.filepath = "/home/kevin/ShanghaiTech/Sophomore/DS/Project/Codes/data/clusters_end.js"
end_dir = io.readin()

start_list = [[i['lng'],i['lat'],i['count']] for i in start_dir]
end_list = [[i['lng'],i['lat'],i['count']] for i in end_dir]
'''
print(start_list)
print(end_list)
'''
result = dd.GrabCab(ptr[0], ptr[1], end_list, start_list)
print(result)
print('time used = %.8f s'%(time.time()-init_time))
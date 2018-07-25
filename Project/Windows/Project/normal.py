import numpy as np

x = np.round(np.random.normal(1.6,1,1200),20)
#print(x)

result = []
for i in x:
	if i > 0:
		result.append(i)

print(len(result))
with open('data_2.txt', 'w') as f:
	f.write(str(result))
	f.close()
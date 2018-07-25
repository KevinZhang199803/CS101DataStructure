with open('data_2.txt') as f, open('output_2.txt', 'w') as g:
	data = eval(f.read())
	for i in data:
		g.write(str(i) + '\n')
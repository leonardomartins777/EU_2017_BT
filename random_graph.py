# -*- coding: latin-1 -*-

import os


tamanho = [10,20,30,40,50]
densidade = [0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9]
seed = [1,2,3,4,5,6,7,8,9,10]

for t in tamanho:
	for d in densidade:
		for s in seed:
			os.system("./random_graph %d %f %d > randomgraph/%d.%.2f.%d " % (t, d, s, t, d, s) )

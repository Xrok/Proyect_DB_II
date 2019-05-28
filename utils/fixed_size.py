

file = open("data_small.csv")
file_out = open("indexs.csv","w+")

#sizes=[5,6,30,2,30,2,2,40,8,5,5,2,4,6,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2]
sizes=[5,6,30,2,30,2,2,40,8,5,5,2,4,6]

for i,fila in enumerate(file):

	for j,atrib in enumerate(fila[:-1].split(',')):

		if len(atrib)>sizes[j]:
			raise Exception("un atributo es mas largo del espacio que se le da",i,j,atrib)

		
		palabra=""
		
		for letra in atrib:
			if ord(letra) < 128:
				palabra=palabra+letra


		num_spaces=sizes[j]-len(palabra)
		
		file_out.write(palabra+' '*num_spaces)

		if j<len(sizes)-1:
			file_out.write(',')
			

	file_out.write('\n')
	

	#ID jughador \\ nro fila
	#
	#



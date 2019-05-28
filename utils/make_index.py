
file = open("data_corrected2.csv")
file_out = open("indexs.csv","w+")

#sizes=[5,6,30,2,30,2,2,40,8,5,5,2,4,6,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2]
#sizes=[5,6,30,2,30,2,2,40,8,5,5,2,4,6]

for i,fila in enumerate(file):

	atributos=fila.split(',')
	reverse=[atributos[1],atributos[0]]
	
	for j,atrib in enumerate(reverse):

	
		palabra=""

		for letra in atrib:
			if letra !=' ':
				palabra=palabra+letra


		#num_spaces=sizes[j]-len(palabra)
		
		file_out.write(palabra)

		if j<1:
			file_out.write(',')
			

	file_out.write('\n')
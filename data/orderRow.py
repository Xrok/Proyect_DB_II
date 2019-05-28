
file = open("data2_1.csv")
file_out = open("data2_3.csv","w+")

#sizes=[5,6,30,2,30,2,2,40,8,5,5,2,4,6,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2]
#sizes=[5,6,30,2,30,2,2,40,8,5,5,2,4,6]

for i,fila in enumerate(file):

    atributos=fila.split(',')
    general=[i,atributos[3],atributos[0],atributos[1],atributos[2],atributos[4]]

    for j,atrib in enumerate(general):



        if j==0:
            atrib=str(atrib)+(' '*(5-len(str(atrib))))


        #num_spaces=sizes[j]-len(palabra)

        file_out.write(str(atrib))

        if j<4:
            file_out.write(',')


    file_out.write('\n')
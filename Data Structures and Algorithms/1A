size=int(input("Enter the table size :"))
n=int(input("\nEnter no .of records to be inserted :"))
hash_table=[-1]*size
def linear_probing(telephone_no):
	for i in range (size):
		index=(telephone_no+i)%size
		if(hash_table[index]==-1):
			hash_table[index]=(telephone_no)
			print("\nRecord Inserted")
			break
		else:
			print("Table Full , Record Cannot be Inserted")
def Quadratic(telephone_no):
	i=0
	for i in range(size):
		index=(telephone_no%size +i*i)%size
		if(hash_table[index]==-1):
			hash_table[index]=(telephone_no)
			print("Record Inserted")
			break
		else:
			i+=1
			if(i==size):
				print("Element Cannot be inserted")
def search(telephone_no):
	count=1
	for i in range (size):
		index=(telephone+i)%size
		if(hash_table[index]==telephone):
			print("Element Found at index ",index)
			print("Required record :",hash_table[index])
			print("No.of comparisons =",count)
			break
		elif(hash_table[index]!=tele):
			i+=1
			count+=1
	else:
		print("Record not found")
def display():
	print("Index Telephone number ")
	for i in range (size):
		if(hash_table[i]!=-1):
			print(i,"  ",hash_table[i])
while(True):
	choice=int(input("\n1.Insert the record using linear probing\n2.Insert record using Quadratic probing \n3.Search\n4.Display record \n5]Exit"))
	if(choice==1):
		for i in range(n):
			teleno=int(input("Enter the telephone_no :"))
			linear_probing(teleno)
	elif(choice==2):
		for i in range(n):
			teleno=int(input("Enter the telephone_no :"))
			Quadratic(teleno)
	elif(choice==3):
		tele_num=int(input("Enter the number to be searched :"))
		search(telephone_num)
	if(choice==4):
		display()
	else:
		print("Program Exited")
		

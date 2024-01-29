# Program to implement Hashing with Linear Probing
from Record import Record

class HashTable:
    def __init__(self):
        self.size = int(input("Enter the Size of the hash table: "))
        self.table = [None] * self.size
        self.elementCount = 0
        self.comparisons = 0

    def isFull(self):
        if self.elementCount == self.size:
            return True
        else:
            return False

    def hashFunction(self, element):
        return element % self.size

    def insert(self, record):
        if self.isFull():
            print("Hash Table Full")
            return False

        isStored = False
        position = self.hashFunction(record.get_number())

        if self.table[position] == None:
            self.table[position] = record
            print("Phone number of " + record.get_name() + " is at position " + str(position))
            isStored = True
            self.elementCount += 1
        else:
            print("Collision has occurred for " + record.get_name() + "'s phone number at position " + str(position) + " finding new Position.")
            while self.table[position] != None:
                position += 1
                if position >= self.size:
                    position = 0
            self.table[position] = record
            print("Phone number of " + record.get_name() + " is at position " + str(position))
            isStored = True
            self.elementCount += 1

        return isStored

    def search(self, record):
        found = False
        position = self.hashFunction(record.get_number())
        self.comparisons += 1

        if self.table[position] != None:
            if self.table[position].get_name() == record.get_name() and self.table[position].get_number() == record.get_number():
                isFound = True
                print("Phone number found at position {} and total comparisons are {}".format(position, 1))
                return position

        else:
            position += 1
            if position >= self.size-1:
                position = 0

            while self.table[position] != None or self.comparisons <= self.size:
                if self.table[position].get_name() == record.get_name() and self.table[position].get_number() == record.get_number():
                    isFound = True
                    i = self.comparisons + 1
                    print("Phone number found at position {} and total comparisons are {}".format(position, i))
                    return position
                position += 1
                if position >= self.size-1:
                    position = 0
                self.comparisons += 1

        if isFound == False:
            print("Record not found")
            return False

    def display(self):
        print("\n")
        for i in range(self.size):
            print("Hash Value: " + str(i) + "\t\t" + str(self.table[i]))

        print("The number of phonebook records in the Table is: " + str(self.elementCount))

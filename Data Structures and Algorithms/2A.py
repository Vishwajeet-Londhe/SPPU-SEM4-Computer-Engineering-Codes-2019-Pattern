class HashTable:
    def __init__(self):
        self.size = 10
        self.slots = [None] * self.size
        self.data = [None] * self.size
        self.indices = [-1] * self.size

    def insert(self, key, data):
        flag = 0
        hashvalue = self.hashfunction(key, len(self.slots))
        same = hashvalue
        if self.slots[hashvalue] == None:
            self.slots[hashvalue] = key
            self.data[hashvalue] = data
        else:
            if self.slots[hashvalue] == key:
                self.data[hashvalue] = data  # replace
            else:
                nextslot = self.nextloc(hashvalue, len(self.slots))
                while self.slots[nextslot] != None and self.slots[nextslot] != key:
                    nextslot = self.nextloc(nextslot, len(self.slots))
                if self.slots[nextslot] == None:
                    self.slots[nextslot] = key
                    self.data[nextslot] = data
                    self.indices[hashvalue] = nextslot
                else:
                    self.data[nextslot] = data  # replace

    def hashfunction(self, key, size):
        return key % size

    def nextloc(self, oldhash, size):
        return (oldhash + 1) % size

    def delete(self, key):
        hashvalue = self.hashfunction(key, len(self.slots))
        flag = False
        check = 0
        while check != 1:
            if self.slots[hashvalue] == key:
                self.slots[hashvalue] = None
                self.data[hashvalue] = None
                self.indices[hashvalue] = -1
                check = 1
                flag = True
                break
            else:
                if self.indices[hashvalue] != -1:
                    oldhash = hashvalue
                    hashvalue = self.indices[hashvalue]
                    self.indices[oldhash] = -1
                else:
                    check = 1
                    break

    def get(self, key):
        startslot = self.hashfunction(key, len(self.slots))
        data = None
        stop = False
        found = False
        position = startslot
        while self.slots[position] != None and not found and not stop:
            if self.slots[position] == key:
                found = True
                data = self.data[position]
            else:
                position = self.nextloc(position, len(self.slots))
            if position == startslot:
                stop = True
        return data

    def __getitem__(self, key):
        return self.get(key)

    def __setitem__(self, key, data):
        self.insert(key, data)


H = HashTable()
H[54] = "Rohit"
H[26] = "Anaya"
H[93] = "Nikita"
H[17] = "Amar"
H[77] = "Manali"
H[31] = "Shilpa"
H[44] = "Aniket"
H[99] = "Prasad"
H[20] = "Pawan"

print("Keys:")
print(H.slots)
print("Data at their respective Keys:")
print(H.data)
print(H.indices)

print(H[77])
H.delete(77)

print("After deletion of data in H[77]")
print("Keys:")
print(H.slots)
print("Data at their respective Keys:")
print(H.data)
print(H.indices)

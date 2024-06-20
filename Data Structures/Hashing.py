class hashing:
    def _init_(self):
        self.size=int(input("enter the size of Hash Table: "))
        self.hashtable=[-1 for i in range(self.size)]
        self.count=0

    def isfull(self):
        if self.count ==self.size:
            return True
        else:
            return False
        
    def Hashfunction(self,ele):
        return ele % self.size
    
    def inserting(self,ele):
        if self.isfull():
            print("Hash Table is full")
        else:
            if(self.hashtable[self.Hashfunction(ele)]==-1):
                self.hashtable[self.Hashfunction(ele)]=ele
                self.count+=1
                print(self.hashtable)
            else:
                self.collision(ele)

    def collision(self,ele):
        self.choice=int(input("choice Technique \n 1. Linear Probing \n 2. Quadratic probing \n"))
        if(self.choice == 1):
            self.linearProb(ele)
        else:
            self.QuadProb(ele)
    
    def linearProb(self,ele):
        self.i=self.Hashfunction(ele)
        while self.hashtable[self.i] !=-1:
            self.i+=1
        self.hashtable[self.i]=ele
        self.count+=1
        print(self.hashtable)

    def QuadProb(self,ele):
        self.j=self.Hashfunction(ele)
        self.l=0
        self.k=((self.j) + (self.l*self.i)) % self.size

        while self.hashtable[self.k] !=-1:
            self.l+=1
            self.k =((self.j)+ (self.l*self.l)) % self.size

        self.hashtable[self.k]=ele
        self.count+=1
        print(self.hashtable)

obj =hashing()
obj._init_()
for i in range(int(input("Enter the number of clients:"))):
    name=input("Enter the name: ")
    ele1=int(input("enter the telephone no.: "))
    obj.inserting(ele1)

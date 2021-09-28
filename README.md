# Kevin-Bacon
Six Degrees of Kevin Bacon or "Bacon's Law" is a parlour game based on the "six degrees of separation" concept, which posits that any two people on Earth are six or fewer acquaintance links apart. Movie buffs challenge each other to find the shortest path between an arbitrary actor and prolific actor Kevin Bacon. It rests on the assumption that anyone involved in the Hollywood film industry can be linked through their film roles to Bacon within six steps.<br/>
The Bacon number of an actor is the number of degrees of separation he or she has from Bacon, as defined by the game. This is an application of the Erdős number concept to the Hollywood movie industry. The higher the Bacon number, the greater the separation from Kevin Bacon the actor is.<br/>
The computation of a Bacon number for actor X is a "shortest path" algorithm, applied to the co-stardom network:<br/>
•	Kevin Bacon himself has a Bacon number of 0.<br/>
•	Those actors who have worked directly with Kevin Bacon have a Bacon number of 1.<br/>
•	If the lowest Bacon number of any actor with whom X has appeared in any movie is N, X's Bacon number is N+1.<br/>

# Examples
Elvis Presley:<br/>
•	Elvis Presley was in Change of Habit (1969) with Edward Asner<br/>
•	Edward Asner was in JFK (1991) with Kevin Bacon<br/>
Therefore, Asner has a Bacon number of 1, and Presley (who never appeared in a film with Bacon) has a Bacon number of 2.<br/>
<br/><br/>
Ian McKellen:<br/>
•	Ian McKellen was in X-Men: Days of Future Past (2014) with Michael Fassbender and James McAvoy<br/>
•	McAvoy and Fassbender were in X-Men: First Class (2011) with Kevin Bacon<br/>
Therefore, McAvoy and Fassbender have Bacon numbers of 1, and McKellen has a Bacon number of 2.<br/>
Because some people have both a finite Bacon and a finite Erdős number because of acting and publications, there are a rare few who have a finite Erdős–Bacon number, which is defined as the sum of a person's independent Erdős and Bacon numbers.

# Hashing
A hash function is any function that can be used to map data of arbitrary size to fixed-size values. The values returned by a hash function are called hash values, hash codes, digests, or simply hashes. The values are used to index a fixed-size table called a hash table. Use of a hash function to index a hash table is called hashing or scatter storage addressing.<br/>
Hash functions and their associated hash tables are used in data storage and retrieval applications to access data in a small and nearly constant time per retrieval, and storage space only fractionally greater than the total space required for the data or records themselves. Hashing is a computationally and storage space efficient form of data access which avoids the non-linear access time of ordered and unordered lists and structured trees, and the often exponential storage requirements of direct access of state spaces of large or variable-length keys.<br/>
A hash function takes as input a key, which is associated with a datum or record and used to identify it to the data storage and retrieval application. The keys may be fixed length, like an integer, or variable length, like a name. In some cases, the key is the datum itself. The output is a hash code used to index a hash table holding the data or records, or pointers to them.
<br/>
Hash functions are used in conjunction with hash tables to store and retrieve data items or data records. The hash function translates the key associated with each datum or record into a hash code which is used to index the hash table. When an item is to be added to the table, the hash code may index an empty slot (also called a bucket), in which case the item is added to the table there. If the hash code indexes a full slot, some kind of collision resolution is required: the new item may be omitted (not added to the table), or replace the old item, or it can be added to the table in some other location by a specified procedure. That procedure depends on the structure of the hash table: In chained hashing, each slot is the head of a linked list or chain, and items that collide at the slot are added to the chain. Chains may be kept in random order and searched linearly, or in serial order, or as a self-ordering list by frequency to speed up access. In open address hashing, the table is probed starting from the occupied slot in a specified manner, usually by linear probing, quadratic probing, or double hashing until an open slot is located or the entire table is probed (overflow). Searching for the item follows the same procedure until the item is located, an open slot is found or the entire table has been searched (item not in table).
<br/>
Linear probing is a component of open addressing schemes for using a hash table to solve the dictionary problem. In the dictionary problem, a data structure should maintain a collection of key–value pairs subject to operations that insert or delete pairs from the collection or that search for the value associated with a given key. 

# BFS algorithm
Breadth-first search (BFS) is an algorithm for traversing or searching tree or graph data structures. It starts at the tree root (or some arbitrary node of a graph, sometimes referred to as a 'search key'), and explores all of the neighbor nodes at the present depth prior to moving on to the nodes at the next depth level.
It uses the opposite strategy as depth-first search, which instead explores the node branch as far as possible before being forced to backtrack and expand other nodes.
## Pseudocode
Input: A graph Graph and a starting vertex root of Graph
Output: Goal state. The parent links trace the shortest path back to root
```
1  procedure BFS(G,start_v):
2      let Q be a queue
3      label start_v as discovered
4      Q.enqueue(start_v)
5      while Q is not empty
6          v = Q.dequeue()
7          if v is the goal:
8              return v
9          for all edges from v to w in G.adjacentEdges(v) do
10             if w is not labeled as discovered:
11                 label w as discovered
12                 w.parent = v
13                 Q.enqueue(w) 
```

# Time complexity
Hashing: Using linear probing, dictionary operations can be implemented in constant expected time. In other words, insert, remove and search operations can be implemented in O(1), as long as the load factor of the hash table is a constant strictly less than one.
<br/>
BFS: 
Worst-Case Time Complexity (Double Hashing)<br/>
•	Find: O(n) — If we are extremely unlucky, we may have to probe over all n elements<br/>
•	Insert: O(n) — If we are extremely unlucky, we may have to probe over all n elements<br/>
•	Remove: O(n) — If we are extremely unlucky, we may have to probe over all n elements<br/>
<br/>
Average-Case Time Complexity (Double Hashing)<br/>
•	Find: O(1) — The formal proof is too complex for a summary slide<br/>
•	Insert: O(1) — The formal proof is too complex for a summary slide<br/>
•	Remove: O(1) — The formal proof is too complex for a summary slide<br/>
<br/>
Best-Case Time Complexity (Double Hashing)<br/>
•	Find: O(1) — No collisions<br/>
•	Insert: O(1) — No collisions<br/>
•	Remove: O(1) — No collisions<br/>

# Algorithm of the code

Using techniques mentioned above code will be run through the algorithm below:
```
-	Initialize lookup table.
-	Find bacon number by using BFS algorithm: where we find the links between the actors and print out the number of actors which are infinite far away from bacon (those actors have no links).
-	After giving an actor name we search in our lookup table for the given actor name by using hashing algorithm, then trying to find the path between given actor name and bacon, if the path is found we return the names of actors linking our actor to bacon with bacon number, otherwise we consider the actor is infinite far away from bacon.
```
# Results
![Result5](https://github.com/shazaalqays/Kevin-Bacon-in-C/blob/main/images/ex1.jpg) <br/><br/>
![Result5](https://github.com/shazaalqays/Kevin-Bacon-in-C/blob/main/images/ex2.jpg) <br/><br/>
![Result5](https://github.com/shazaalqays/Kevin-Bacon-in-C/blob/main/images/ex3.jpg) <br/><br/>
![Result5](https://github.com/shazaalqays/Kevin-Bacon-in-C/blob/main/images/ex4.jpg) <br/><br/>
![Result5](https://github.com/shazaalqays/Kevin-Bacon-in-C/blob/main/images/ex5.jpg) <br/><br/>
![Result5](https://github.com/shazaalqays/Kevin-Bacon-in-C/blob/main/images/ex6.jpg) <br/><br/>
![Result5](https://github.com/shazaalqays/Kevin-Bacon-in-C/blob/main/images/ex7.jpg) <br/><br/>
![Result5](https://github.com/shazaalqays/Kevin-Bacon-in-C/blob/main/images/ex8.jpg) <br/><br/>

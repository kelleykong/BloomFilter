BloomFilter
===========

Dictionary with Bloom Filter algorithm by C++

==============================================

It's a project I finished in Oct. 2010 when I'm a sophomore student in Nanjing University.
It is just a class project, by which Data Structure teacher hopes us to get a skill to learn a new algorithm 
related with our class by ourself and learn to implement it. 

Bloom Filter is an algorithm similar with HashTable. 
HashTable needs to store all data. When you look up a data, get the hash value, compare the data stored in the location of hash value with the data you check. HashTable also deals with collisions.
Bloom Filter doesn't store all data. Many hash functions will be used. It maintains a bit table, in which the bit of hash value will be set as 1. When you look up a data, check whether all bits in the locations of hash value are 1. There may be some errors, some data don't exist in the database may be regarded as in the database. Because Bloom Filter doesn't deal with collisions.

I apply Bloom Filter to a dictionary application. When users want to find a word, the Bloom Filter will help to find
the word in the dictionary. There may be some errors but Bloom Filter really reduces the time consumption to loop up 
the dictionary from O(N) to O(1).

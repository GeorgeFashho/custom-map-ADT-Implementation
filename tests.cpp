/*tests.cpp  - Test cases written with Gtest to test mymap.h header files

            written by: [George Fashho] + Various Authors on [15/11/2022] for [CS 251 FA22]
            
            *Authors given credit above test suite*
 */


#include <gtest/gtest.h>
#include "mymap.h"
#include <random> 
#include "myrandom.h"
#include <vector>


//gfash2 Test cases
TEST(mymap, one) {
    
    mymap<int,int> map; 
    vector<pair<int,int>>test ; 
    

    EXPECT_EQ(map.Size() == 0 , true);

    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }


    EXPECT_EQ(map.Size(), 3);
    
    for (int i = 0; i < 3; i++) {

    EXPECT_TRUE(map.contains(arr[i]));
    
    }
    
    for (int i = 100 ; i < 1000 ; i++){
        EXPECT_FALSE(map.contains(i)) ;
    } 
        

    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(map.get(arr[i]), arr[i]);
        EXPECT_EQ(map.Size(), 3);
    
    }

    string sol = "key: 1 value: 1\nkey: 2 value: 2\nkey: 3 value: 3\n" ;
    string checkBalanceStr = "key: 2, nL: 1, nR: 1\nkey: 1, nL: 0, nR: 0\nkey: 3, nL: 0, nR: 0\n";


    mymap<int, int> mapCopy2 = map;



    map.toString();
    
    EXPECT_EQ(checkBalanceStr, map.checkBalance()); 

    EXPECT_EQ(sol,mapCopy2.toString());    

    EXPECT_EQ(sol, map.toString());    

    for (int i = 0; i < 3; i++) {

        EXPECT_EQ(map[arr[i]], arr[i]);
        EXPECT_EQ(map.Size(), 3);
    }

    map[5000];

    EXPECT_EQ(map[5000], 0);

    EXPECT_EQ(map.Size(), 4);


    mymap<int,int>mapCopy;

    mapCopy = map;

    EXPECT_EQ(mapCopy.Size(),map.Size()) ; 
    
    
    map.clear();

    cout<<"Clear Works!"<<endl;

    mapCopy2.clear();
    cout<<"Clear Works!"<<endl;

}

// Test for operator[] on already balanced tree.
// netid: lsasu2
 TEST(mymap, operatorBrackets){
    
    mymap<int, string> test;
    map<int, string> omap;
    int n= 10;
    int arr[] = {40, 25, 60, 18, 35, 80, 30, 38, 50, 70};

    for (int i = 0; i < n; i++) {
        string value = "MAX: " + to_string(rand() % 40);
        test.put(arr[i], value);
        omap.emplace(arr[i], value);
    }
    for(int i=0; i<n;i++){
        ASSERT_EQ(test[arr[i]], omap[arr[i]]);
    }

    //Value not in map
    for(int i=0; i<n;i++){
        ASSERT_EQ(test[i*1000], "");
        ASSERT_EQ(test.Size(), n+i+1);
    }

    //Duplicate values
    for (int i = 0; i < n; i++) {
        string value = "MAX: " + to_string(rand()%40);
        test.put(arr[i], value);
        omap[arr[i]] = value;
    }
    for(int i=0; i<n;i++){
        ASSERT_EQ(test[arr[i]], omap[arr[i]]);
    }

/*     cout<<test.toString();
 */
   test.clear();
    cout<<"Clear Works"<<endl;
    // omap.clear();

} 

TEST(myMap, Milestone3){


    mymap<int, int> map;

    int arr[] = {2, 1, 3};
    int order[] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }

    int i = 0;

    for (auto key : map) {
        EXPECT_EQ(order[i++], key);
    }
 
    map.clear();
 }

// // netid: rshah268
// // Copy and Clear Stress Test
TEST(mymap, Copy) {
    
    // Create two mymaps m1 and m2
    mymap<int, int> m1;
    mymap<int, int> m2;
    int n = 10000;

    for(int  i = 0; i < n; i++) {

        // Generate two random numbers
        int key = randomInteger(0, 100000);
        int val = randomInteger(0, 100000);

        // Insert them in map1
        m1.put(key, val);

        // Insert different elements in map2
        if(i % 2) {
            m2.put(val, key);
        }
    }

    // At this point they must be unequal
    ASSERT_NE(m1.Size(), m2.Size());

    // Set map2 equals to map1
    m2 = m1;

    // Both should be the same size and contain the same elements
    ASSERT_EQ(m1.Size(), m2.Size());
    ASSERT_EQ(m1.toString(), m2.toString());

    // Clear map1
      m1.clear();
 
    // Now they are unequal again
    ASSERT_NE(m1.Size(), m2.Size());
    // Map1 must be empty
    ASSERT_EQ(m1.Size(), 0);
}

TEST(mymap, stressTest){


    mymap<int, int> mapMine;
    map<int, int> mapSol;
    int n = 1000000;
    for (int i = 1; i <= n; i++) {
        int key = randomInteger(0, 10000);
        int val = randomInteger(0, 10000);
        mapMine.put(key, val);
        mapSol[key] = val;
    }

    EXPECT_EQ(mapMine.Size(), mapSol.size());

    stringstream solution("");
    for (auto e : mapSol) {
        solution << "key: " << e.first << " value: " << e.second << endl;
        EXPECT_TRUE(mapMine.contains(e.first));
        EXPECT_EQ(mapMine.get(e.first), e.second);
    }

    EXPECT_EQ(mapMine.toString(), solution.str());
}
//gfash2
TEST(mymap, Char){

    mymap<char, char> charMap ;

    char array[] = {'a','b','c','d','e','f','g','h','i'};


    for(int i = 0 ; i < 9 ; i++){

        charMap.put(array[i],array[i]);
        EXPECT_EQ(charMap.Size(), i+1);
    }

    for (int i = 0; i < 9; i++) {

    EXPECT_TRUE(charMap.contains(array[i]));
    
    }

    for (int i = 0; i < 9; i++) {
        EXPECT_EQ(charMap.get(array[i]), array[i]);
        EXPECT_EQ(charMap.Size(), 9);
    
    }

    string sol = "key: a value: a\nkey: b value: b\nkey: c value: c\nkey: d value: d\nkey: e value: e\nkey: f value: f\nkey: g value: g\nkey: h value: h\nkey: i value: i\n" ;

    mymap<char, char> charMapCopy2 = charMap;


    EXPECT_EQ(sol,charMapCopy2.toString());    

    EXPECT_EQ(sol, charMap.toString());    

    charMap['z'];

    EXPECT_EQ(charMap['z'],'\u0000');

}

//gfash2
TEST(mymap, STR){

    mymap<string, string> StrMap ;

    string array[] = {"ab","cd","ef","gh","ij","kl","mn","op","qr"};


    for(int i = 0 ; i < 9 ; i++){

        StrMap.put(array[i],array[i]);
        EXPECT_EQ(StrMap.Size(), i+1);
    }

     for (int i = 0; i < 9; i++) {

    EXPECT_TRUE(StrMap.contains(array[i]));
    
    }

    for (int i = 0; i < 9; i++) {
        EXPECT_EQ(StrMap.get(array[i]), array[i]);
        EXPECT_EQ(StrMap.Size(), 9);
    
    }

    string sol = "key: ab value: ab\nkey: cd value: cd\nkey: ef value: ef\nkey: gh value: gh\nkey: ij value: ij\nkey: kl value: kl\nkey: mn value: mn\nkey: op value: op\nkey: qr value: qr\n" ;

    mymap<string, string> StrMapCopy2 = StrMap;


    EXPECT_EQ(sol,StrMapCopy2.toString());    

    EXPECT_EQ(sol, StrMap.toString());    

    StrMap["Zzz"];

/*      EXPECT_EQ(StrMap["Zzz"],nullptr); 
 */  
} 


//tkoope2
//Copy Operator test <int, int>
TEST(Operator, IICopyP) {
 mymap<int, int> m;
 mymap<int, int> m2;

 //Populate 1 and 2
 int key, value, high, low, modOp;
 int arrSize = rand() % 100;

 string mOriginal, m2Original;

 //Populate m
 high = 500;
 low = 1;
 modOp = (high - (low + 1)) + low;
 for (int i = 0; i < arrSize; i++) {
  key = rand() % modOp;
  value = rand() % modOp;
  m.put(key, value);
 }

 //Populate m2
 high = 1000; 
 low = 500;
 modOp = (high - (low + 1)) + low;
 for (int i = 0; i < arrSize; i++) {
  key = rand() % modOp;
  value = rand() % modOp;
  m2.put(key, value);
 }

 m = m2;

 EXPECT_EQ(m.Size(), m2.Size()) << "IIEquals; size difference\n";
 EXPECT_NE(mOriginal, m.toString()) << "m should not still equal original\n";
 EXPECT_EQ(m2.toString(), m.toString()) << "toString() !=\n" << "M:\n" << m.toString() << "\nM2:\n" << m2.toString() << endl;;
}



//tkoope2
//Copy Constructor
TEST(copyConstructor, IIConCopy) {
 mymap<int, int> m;
 map<int, int> correct;
 vector<int> keys;
 int key;
 int val;
 int arrSize = 15;
 int high = 500, low = 0;
 int modOp = (high - (low + 1)) + low;


 //Populate
 for (int i = 0; i < arrSize; i++) {
  key = rand() % modOp;
  val = rand() % modOp;

  keys.push_back(key);

  m.put(key, val);
  correct[key] = val;
 }

 EXPECT_EQ(m.Size(), correct.size()) << "mymap != map\n";
 
 mymap<int, int> m2 = m;
 EXPECT_EQ(m.toString(), m2.toString()) << "Copy operator formating off\n";
 EXPECT_EQ(m2.Size(), correct.size()) << "M2's size does not match correct's\n";

 //Both have the same return value on keys
 int compA;
 int compB;
 for (auto& k : keys) {
  compA = m2[k];
  compB = correct[k];
  EXPECT_EQ(compA, compB) << compA << " != " << compB << "\t Incorrect Copy Constructor\n";
 }
}

// milestone 1 tests 
// ssulta24
// default constructor Test and size Test
TEST(mymap, defaultConstructor) {

    // create a mymap
    mymap<int, int> m; 

    // check if the size is 0
    EXPECT_EQ(m.Size(), 0);

}

// ssulta24
// put Test and size Test
TEST(mymap, put) {

    // create a mymap
    mymap<int, int> m; 

    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        m.put(arr[i], arr[i]);
    }
    EXPECT_EQ(m.Size(), 3);

}

// ssulta24
// get Test
TEST(mymap, get) {

    // create a mymap
    mymap<int, int> m; 

    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        m.put(arr[i], arr[i]);
    }
    EXPECT_EQ(m.get(1), 1);
    EXPECT_EQ(m.get(2), 2);
    EXPECT_EQ(m.get(3), 3);
    EXPECT_EQ(m.get(4), 0);

}

// ssulta24
// contains Test
TEST(mymap, containsKey) {

    // create a mymap
    mymap<int, int> m; 

    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        m.put(arr[i], arr[i]);
    }
    EXPECT_EQ(m.contains(1), true);
    EXPECT_EQ(m.contains(2), true);
    EXPECT_EQ(m.contains(3), true);
    EXPECT_EQ(m.contains(4), false);

}

// ssulta24
// toString Test
TEST(mymap, tostr) {

    // create a mymap
    mymap<int, int> m; 

    int arr[] = {3, 2, 1};
    for (int i = 0; i < 3; i++) {
        m.put(arr[i], arr[i]);
    }
    string sol = "key: 1 value: 1\nkey: 2 value: 2\nkey: 3 value: 3\n";
    EXPECT_EQ(sol, m.toString());

}

// ssulta24
// operator[] Test
TEST(mymap, operator) {

    // create a mymap
    mymap<int, int> m; 

    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        m.put(arr[i], arr[i]);
    }
    EXPECT_EQ(m[1], 1);
    EXPECT_EQ(m[2], 2);
    EXPECT_EQ(m[3], 3);
    EXPECT_EQ(m[4], 0);

}


TEST(mymap, stringTest){

    mymap<string,string>testerMap ; 

}

// ssulta24
// stress test combining all the tests above 
TEST(mymap, stressTest2) {

    // create a mymap
    mymap<int, int> m; 

    vector< int > arr;

    for (int i = 0; i < 10000; i++) {
        int num = randomInteger(0, 10000);
        // append num to arr 
        arr.push_back(num);
        m.put(i, num);
    }

    for (int i = 0; i < 10000; i++) {
        EXPECT_EQ(m[i], arr[i]);
    }

    for (int i = 0; i < 10000; i++) {
        EXPECT_EQ(m.contains(i), true);
    }

    for (int i = 0; i < 10000; i++) {
        EXPECT_EQ(m.get(i), arr[i]);
    }

    EXPECT_EQ(m.Size(), 10000);

}

// netid: msiddi73
// Testing Put with random int key (Testing Size and toString)
TEST(Put, randomIntInt){

    map<int, int> m;
    mymap <int, int> mymap;
    stringstream s;

    int randomKey = 0;
    int randomValue = 0;
    int randomSize = 0;
    string test;
    
    for (int i = 0; i < 35; i++){

        test = "";
        s.str("");

        randomSize = randomInteger(1, 50);

        for (int p = 0; p < randomSize; p++){
                
            randomKey = randomInteger(0, 100);
            randomValue = randomInteger(0, 100);

            m[randomKey] = randomValue;
            mymap.put(randomKey, randomValue);

        }

        for (auto const& x : m){
            s << "key: " << x.first << " value: " << x.second << "\n";
        }

        test = mymap.toString();

        ASSERT_EQ(mymap.Size(), m.size());
        ASSERT_EQ(test, s.str());

        mymap.clear();
        m.clear();
        
    }

}

// netid: msiddi73
// Testing put with random char key (Testing Size and toString)
TEST(Put, randomCharInt){

    map<char, int> m;
    mymap <char, int> mymap;
    stringstream s;

    char randomKey = 0;
    int randomValue = 0;
    int randomSize = 0;
    string test;
    

    for (int i = 0; i < 35; i++){

        test = "";
        s.str("");

        randomSize = randomInteger(1, 50);

        for (int p = 0; p < randomSize; p++){
                
            randomKey = randomInteger(65, 90); // get uppercase characthers
            randomValue = randomInteger(0, 100);

            m[randomKey] = randomValue;
            mymap.put(randomKey, randomValue);

        }

        for (auto const& x : m){
            s << "key: " << x.first << " value: " << x.second << "\n";
        }

        test = mymap.toString();

        ASSERT_EQ(mymap.Size(), m.size());
        ASSERT_EQ(test, s.str());

         mymap.clear();
        m.clear();
         
    }

}

// netid: msiddi73
// Testing Put with random string key (Testing Size and toString)
TEST(Put,StringInt){

    const string characthers = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    map<string, int> m;
    mymap <string, int> mymap;
    stringstream s;

    string randomKey = "";
    int randomValue = 0;
    int randomSize = 0;
    string test;
    

    for (int i = 0; i < 35; i++){

        test = "";
        s.str("");

        randomSize = randomInteger(1, 50);

        for (int p = 0; p < randomSize; p++){
                
            for (int i = 0 ; i < 6; i++){
                randomKey += characthers[randomInteger(0,characthers.size() - 1)];
            }

            randomValue = randomInteger(0, 100);

            m[randomKey] = randomValue;
            mymap.put(randomKey, randomValue);

        }

        for (auto const& x : m){
            s << "key: " << x.first << " value: " << x.second << "\n";
        }

        test = mymap.toString();


        ASSERT_EQ(mymap.Size(), m.size());
        ASSERT_EQ(test, s.str());

         mymap.clear();
        m.clear();
       
    }

}

// netid: mrush6
// Mustafa Rushdi
// Tests all milestones including rebalancing
/*  TEST(mymap, ZigZagRight)
{
    map<int, char> mapTest;
    vector<int> testVec;
    string s = "";
    vector<pair<int, char>> v;
    mymap<int, char> map2;
    int stringArr[] = {1,10,2,9,3,8,4,7,5,6};
    char charArr1[] = {'l','g','i','p','o','a','f','n','m','y'};
    for (int i = 0; i < 10; i++)
    {
        map2.put(stringArr[i], charArr1[i]);
        EXPECT_TRUE(map2.contains(stringArr[i]));
        EXPECT_EQ(map2.get(stringArr[i]), charArr1[i]);
        EXPECT_EQ(map2[(stringArr[i])], charArr1[i]);
        mapTest[stringArr[i]] = charArr1[i];
    }
    s += "key: 5, nL: 4, nR: 5\n";
    s += "key: 2, nL: 1, nR: 2\n";
    s += "key: 1, nL: 0, nR: 0\n";
    s += "key: 3, nL: 0, nR: 1\n";
    s += "key: 4, nL: 0, nR: 0\n";
    s += "key: 8, nL: 2, nR: 2\n";
    s += "key: 7, nL: 1, nR: 0\n";
    s += "key: 6, nL: 0, nR: 0\n";
    s += "key: 9, nL: 0, nR: 1\n";
    s += "key: 10, nL: 0, nR: 0\n";
    EXPECT_EQ(map2.checkBalance(), s);
    s = "";
    EXPECT_FALSE(map2.contains(0));
    EXPECT_TRUE(map2.contains(1));
    EXPECT_EQ(map2.get(11), {});
    EXPECT_EQ(map2.Size(), 10);
    EXPECT_EQ(map2[11], {});
    s += "key: 5, nL: 4, nR: 6\n";
    s += "key: 2, nL: 1, nR: 2\n";
    s += "key: 1, nL: 0, nR: 0\n";
    s += "key: 3, nL: 0, nR: 1\n";
    s += "key: 4, nL: 0, nR: 0\n";
    s += "key: 8, nL: 2, nR: 3\n";
    s += "key: 7, nL: 1, nR: 0\n";
    s += "key: 6, nL: 0, nR: 0\n";
    s += "key: 10, nL: 1, nR: 1\n";
    s += "key: 9, nL: 0, nR: 0\n";
    s += "key: 11, nL: 0, nR: 0\n";
    EXPECT_EQ(map2.checkBalance(),s);
    mapTest[11];
    stringstream ss;
    for (auto e : mapTest)
    {
        testVec.push_back(e.first);
        ss << "key: " << e.first << " value: " << e.second << endl;
        v.push_back(make_pair(e.first,e.second));
    }
    EXPECT_EQ(map2.toVector(),v);
 
    
    EXPECT_EQ(ss.str(), map2.toString());
    int i = 0;
    for (auto b : map2)
    {
        EXPECT_EQ(testVec.at(i++), b);
    }
    mymap<int, char> mapCopy = map2;
    i = 0;
    for (auto b : mapCopy)
    {
        EXPECT_EQ(testVec.at(i++), b);
    }
    EXPECT_EQ(mapCopy.toVector(),v);
    EXPECT_EQ(mapCopy.toVector(),map2.toVector());
    EXPECT_EQ(mapCopy.checkBalance(),s);
    EXPECT_EQ(mapCopy.checkBalance(),map2.checkBalance());
    EXPECT_EQ(mapCopy.toString(), map2.toString());
    EXPECT_EQ(mapCopy.toString(), ss.str());
    EXPECT_EQ(mapCopy.Size(), map2.Size());
    mymap<int, char> mapCopy2;
    mapCopy2 = map2;
    i = 0;
    for (auto b : mapCopy2)
    {
        EXPECT_EQ(testVec.at(i++), b);
    }
    EXPECT_EQ(mapCopy2.checkBalance(),mapCopy.checkBalance());
    EXPECT_EQ(mapCopy2.checkBalance(),s);
    EXPECT_EQ(mapCopy2.toVector(),v);
    EXPECT_EQ(mapCopy2.toVector(),map2.toVector());
    EXPECT_EQ(mapCopy2.toVector(),mapCopy.toVector());
    EXPECT_EQ(mapCopy2.Size(), mapCopy.Size());
    EXPECT_EQ(mapCopy2.toString(), mapCopy.toString());
    EXPECT_EQ(mapCopy2.toString(), map2.toString());
    EXPECT_EQ(mapCopy2.toString(), ss.str());
    map2.clear();
    mapCopy.clear();
    mapCopy2.clear();
    EXPECT_EQ(map2.Size(), 0);
    EXPECT_EQ(mapCopy.Size(), 0);
    EXPECT_EQ(mapCopy2.Size(), 0);
    ss.str("");
    EXPECT_EQ(map2.toString(), ss.str());
    EXPECT_EQ(mapCopy.toString(), ss.str());
    EXPECT_EQ(mapCopy2.toString(), ss.str());
    EXPECT_EQ(map2.checkBalance(), ss.str());
    EXPECT_EQ(mapCopy.checkBalance(), ss.str());
    EXPECT_EQ(mapCopy2.checkBalance(), ss.str());
    EXPECT_NE(map2.toVector(), v);
    EXPECT_NE(mapCopy.toVector(), v);
    EXPECT_NE(mapCopy2.toVector(), v);
    EXPECT_FALSE(map2.contains(5));
    EXPECT_FALSE(map2.contains(2));
    EXPECT_FALSE(map2.contains(1));
    s = "";
    s += "key: 5, nL: 4, nR: 5\n";
    s += "key: 2, nL: 1, nR: 2\n";
    s += "key: 1, nL: 0, nR: 0\n";
    s += "key: 3, nL: 0, nR: 1\n";
    s += "key: 4, nL: 0, nR: 0\n";
    s += "key: 8, nL: 2, nR: 2\n";
    s += "key: 7, nL: 1, nR: 0\n";
    s += "key: 6, nL: 0, nR: 0\n";
    s += "key: 9, nL: 0, nR: 1\n";
    s += "key: 10, nL: 0, nR: 0\n";
    EXPECT_EQ(map2[1], {});
    EXPECT_EQ(map2[10], {});
    EXPECT_EQ(map2[2], {});
    EXPECT_EQ(map2[9], {});
    EXPECT_EQ(map2[3], {});
    EXPECT_EQ(map2[8], {});
    EXPECT_EQ(map2[4], {});
    EXPECT_EQ(map2[7], {});
    EXPECT_EQ(map2[5], {});
    EXPECT_EQ(map2[6], {});
    EXPECT_EQ(map2.checkBalance(), s);
}
  */
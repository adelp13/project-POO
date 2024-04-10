**OOP project in C++**

The APP focuses on the activity of an electronics store.

**Classes**: <br>-Advertisement <br>-Item<br> Customer<br>- 4 classes applying diamond inheritance; the difference between contests is the type of price which matters in the implementation of different methods (overriding): <br> &emsp;Contest(abstract), ContestPrizeMoney (the prize is given in money),
ContestPrizeItem (the prize is an item from the store), ContestBothPrizes (the class on the bottom)
<br>
-Question (a contest has more questions)<br>
-An interface for reading and writing (abstract functions)
-ContestData - retaining more data about a contest(ex: if it gor approved); an attribute is a pointer to the Contest mentioned (polimorphism) <br>
<br>Menu have different kinds of options each deriving in more possible options:
![image](https://github.com/adelp13/project-POO/assets/116973684/8d18b43c-3d71-4884-ab06-07170a1402ea)
<br> "Functionalities option" shows the menu below:
![image](https://github.com/adelp13/project-POO/assets/116973684/f926a8da-e4d5-4d3d-bda4-1fb0ecc9c614)

The code also makes use of: <br> -overloading of operators such as +, -, *, -- <br>
-runtime errors, constructors and = operator  <br>
- << and >> operators overloading for objects (for reading and writing), cast operator <br>
- upcasting, downcasting, friend operators, STL such as vectors, sets, maps<br>

  <br>
<br> <br>
Code version 2 restricts the classes on the Question, diamond of contests and ContestData, but it adds a singletone class OnlinePlatform, which will be the menu. The second version also implements:<br> - some classes inheriting the exception class for runtime errors (what() function)<br>- template functions: <br> &emsp; -one for verifying input <br> &emsp; - calculateWroth(), which goes through the list of contests and calculates something for one of the three types of contests, using typeid to find the type of the pointer Contest. It applies dynamic_cast to use a function overriden in the diamond.<br>
**Version 2 menu:**
![image](https://github.com/adelp13/project-POO/assets/116973684/7f6e8779-6a89-4697-8ebc-b1a3795cd462)

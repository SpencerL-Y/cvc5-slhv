/******************************************************************************

 * Top contributors (to current version):

 *   Yoni Zohar, Aina Niemetz, Gereon Kremer

 *

 * This file is part of the cvc5 project.

 *

 * Copyright (c) 2009-2024 by the authors listed in the file AUTHORS

 * in the top-level source directory and their institutional affiliations.

 * All rights reserved.  See the file COPYING in the top-level source

 * directory for licensing information.

 * ****************************************************************************

 *

 * A simple demonstration of the API capabilities of cvc5.

 *

 */


#include <cvc5/cvc5.h>


#include <iostream>

#include <numeric>


using namespace cvc5;

/******************************************************************************

 * Top contributors (to current version):

 *   Yoni Zohar, Aina Niemetz, Gereon Kremer

 *

 * This file is part of the cvc5 project.

 *

 * Copyright (c) 2009-2024 by the authors listed in the file AUTHORS

 * in the top-level source directory and their institutional affiliations.

 * All rights reserved.  See the file COPYING in the top-level source

 * directory for licensing information.

 * ****************************************************************************

 *

 * A simple demonstration of the API capabilities of cvc5.

 *

 */


#include <cvc5/cvc5.h>


#include <iostream>

#include <numeric>


using namespace cvc5;


int main()

{

  // Create a term manager

  //! [docs-cpp-quickstart-0 start]

  TermManager tm;

  //! [docs-cpp-quickstart-0 end]

  // Create a solver

  //! [docs-cpp-quickstart-1 start]

  Solver solver(tm);

  //! [docs-cpp-quickstart-1 end]


  // We will ask the solver to produce models and unsat cores,

  // hence these options should be turned on.

  //! [docs-cpp-quickstart-2 start]
  
  solver.setOption("produce-models", "true");

  solver.setOption("produce-unsat-cores", "true");

  //! [docs-cpp-quickstart-2 end]


  // The simplest way to set a logic for the solver is to choose "ALL".

  // This enables all logics in the solver.

  // Alternatively, "QF_ALL" enables all logics without quantifiers.

  // To optimize the solver's behavior for a more specific logic,

  // use the logic name, e.g. "QF_BV" or "QF_AUFBV".


  // Set the logic

  //! [docs-cpp-quickstart-3 start]

  solver.setLogic("ALL");

  //! [docs-cpp-quickstart-3 end]


  // In this example, we will define constraints over reals and integers.

  // Hence, we first obtain the corresponding sorts.

  //! [docs-cpp-quickstart-4 start]

  Sort realSort = tm.getRealSort();

  Sort intSort = tm.getIntegerSort();

  //! [docs-cpp-quickstart-4 end]


  // x and y will be real variables, while a and b will be integer variables.

  // Formally, their cpp type is Term,

  // and they are called "constants" in SMT jargon:

  //! [docs-cpp-quickstart-5 start]

  Term x = tm.mkConst(realSort, "x");

  Term y = tm.mkConst(realSort, "y");

  Term a = tm.mkConst(intSort, "a");

  Term b = tm.mkConst(intSort, "b");

  //! [docs-cpp-quickstart-5 end]


  // Our constraints regarding x and y will be:

  //

  //   (1)  0 < x

  //   (2)  0 < y

  //   (3)  x + y < 1

  //   (4)  x <= y

  //


  //! [docs-cpp-quickstart-6 start]

  // Formally, constraints are also terms. Their sort is Boolean.

  // We will construct these constraints gradually,

  // by defining each of their components.

  // We start with the constant numerals 0 and 1:

  Term zero = tm.mkReal(0);


  Term one = tm.mkReal(1);
  Term two = tm.mkReal(2);


  // Next, we construct the term x + y

  Term xPlusY = tm.mkTerm(Kind::ADD, {x, y});

  Term xMinus2 = tm.mkTerm(Kind::SUB, {x, two});


  // Now we can define the constraints.

  // They use the operators +, <=, and <.

  // In the API, these are denoted by ADD, LEQ, and LT.

  // A list of available operators is available in:

  // src/api/cpp/cvc5_kind.h

  Term constraint1 = tm.mkTerm(Kind::LT, {x, zero});

  Term constraint2 = tm.mkTerm(Kind::LT, {xMinus2, zero});

  Term constraint3 = tm.mkTerm(Kind::LT, {xPlusY, one});

  Term constraint4 = tm.mkTerm(Kind::GT, {xMinus2, one});
  // Term constraint4 = tm.mkTerm(Kind::LEQ, {x, y});

  Term slhv_term1 = tm.mkTerm(Kind::SLHV_PTO, {a, a});
  std::cout << "slhv pto creation finished" << std::endl;
  Term slhv_term2 = tm.mkSLHVEmp();
  std::cout << "slhv emp creation finished" << std::endl;
  Term slhv_term3 = tm.mkTerm(Kind::SLHV_BLK, {slhv_term1, a, a});
  std::cout << "slhv blk creation finished" << std::endl;
  Term slhv_term4 = tm.mkTerm(Kind::SLHV_DISJU, {slhv_term1, slhv_term2, slhv_term1});
  std::cout << "slhv disju creation finished" << std::endl;
  Term slhv_term5 = tm.mkTerm(Kind::SLHV_UNDEF, {slhv_term1});
  std::cout << "slhv undef creation finished" << std::endl;


  Term slhv_constraint_1 = tm.mkTerm(Kind::EQUAL, {slhv_term1, slhv_term2});
  Term slhv_constraint_2 =  slhv_term3;
  std::cout << "begin slhv and" << std::endl;
  Term slhv_constraint = tm.mkTerm(Kind::AND, {slhv_constraint_1, slhv_constraint_2});
  std::cout << "end slhv and" << std::endl;

  Term first_disjunct = tm.mkTerm(Kind::AND, {constraint1, constraint2});
  Term second_disjunct = tm.mkTerm(Kind::AND, {constraint3, constraint4});
  Term final_constraint = tm.mkTerm(Kind::OR, {first_disjunct, second_disjunct});
  // Now we assert the constraints to the solver.
  // solver.assertFormula(final_constraint);
  solver.assertFormula(slhv_constraint);

  // solver.assertFormula(constraint1);

  // solver.assertFormula(constraint2);

  // solver.assertFormula(constraint3);

  // solver.assertFormula(constraint4);

  //! [docs-cpp-quickstart-6 end]


  // Check if the formula is satisfiable, that is,

  // are there real values for x and y that satisfy all the constraints?

  //! [docs-cpp-quickstart-7 start]
  std::cout << "begin checkSat()" << std::endl;
  Result r1 = solver.checkSat();
  std::cout << "end checkSat()" << std::endl; 

  //! [docs-cpp-quickstart-7 end]


  // The result is either SAT, UNSAT, or UNKNOWN.

  // In this case, it is SAT.

  //! [docs-cpp-quickstart-8 start]

  std::cout << "expected: sat" << std::endl;

  std::cout << "result: " << r1 << std::endl;

  //! [docs-cpp-quickstart-8 end]


  // We can get the values for x and y that satisfy the constraints.

  //! [docs-cpp-quickstart-9 start]

  Term xVal = solver.getValue(x);

  Term yVal = solver.getValue(y);

  //! [docs-cpp-quickstart-9 end]


  // It is also possible to get values for compound terms,

  // even if those did not appear in the original formula.

  //! [docs-cpp-quickstart-10 start]

  Term xMinusY = tm.mkTerm(Kind::SUB, {x, y});

  Term xMinusYVal = solver.getValue(xMinusY);

  //! [docs-cpp-quickstart-10 end]


  // We can now obtain the string representations of the values.

  //! [docs-cpp-quickstart-11 start]

  std::string xStr = xVal.getRealValue();

  std::string yStr = yVal.getRealValue();

  std::string xMinusYStr = xMinusYVal.getRealValue();


  std::cout << "value for x: " << xStr << std::endl;

  std::cout << "value for y: " << yStr << std::endl;

  std::cout << "value for x - y: " << xMinusYStr << std::endl;

  //! [docs-cpp-quickstart-11 end]


  //! [docs-cpp-quickstart-12 start]

  // Further, we can convert the values to cpp types

  std::pair<int64_t, uint64_t> xPair = xVal.getReal64Value();

  std::pair<int64_t, uint64_t> yPair = yVal.getReal64Value();

  std::pair<int64_t, uint64_t> xMinusYPair = xMinusYVal.getReal64Value();


  std::cout << "value for x: " << xPair.first << "/" << xPair.second

            << std::endl;

  std::cout << "value for y: " << yPair.first << "/" << yPair.second

            << std::endl;

  std::cout << "value for x - y: " << xMinusYPair.first << "/"

            << xMinusYPair.second << std::endl;

  //! [docs-cpp-quickstart-12 end]


  // Another way to independently compute the value of x - y would be

  // to perform the (rational) arithmetic manually.

  // However, for more complex terms,

  // it is easier to let the solver do the evaluation.

  //! [docs-cpp-quickstart-13 start]

  std::pair<int64_t, uint64_t> xMinusYComputed = {

    xPair.first * yPair.second - xPair.second * yPair.first,

    xPair.second * yPair.second

  };

  uint64_t g = std::gcd(xMinusYComputed.first, xMinusYComputed.second);

  xMinusYComputed = { xMinusYComputed.first / g, xMinusYComputed.second / g };

  if (xMinusYComputed == xMinusYPair)

  {

    std::cout << "computed correctly" << std::endl;

  }

  else

  {

    std::cout << "computed incorrectly" << std::endl;

  }

  return 0;

}
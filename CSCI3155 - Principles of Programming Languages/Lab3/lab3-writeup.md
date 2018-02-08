Raymond Duncan
Anh-Khoa Than
Lab3 Writeup

2a) Give one test case that behaves differently under dynamic scoping versus static scoping (and does not crash). Explain the test case and how they behave differently in your writeup

3d) Explain whether the evaluation order is deterministic as specified by the judgement form e->e'

Evaluation order is deterministic as specified by the judgement form e->e' because different evaluation orders may lead to different evaluation. It is the job of the parser to decide in which order to evaluate the expressions.

4) Condider the small-step operational sematics for JAVASCRIPTY shown in Figures 7, 8, 9. What is the evaluation order for e1 + e2? Explain. How do we change the rules obtain the opposite evaluation order?

Given the small-step operational semantics in figure 8 (SearchBinary) e1 is always evaluated before e2. Essentially the rule says to take any binary expression (plus included) and return the expression with e1 evaluated by one step, and later in SearchBinaryArith is when e2 is stepped. If we wanted to obtain the opposite evaluation order, we would just need to swap e2 for e1 in SearchBinary and e1 for e2 in SearchBinaryArith

5a) Give an example tha illustrates the usefulness of short-circuit evaluation. Explain your example.

An example that illustrates the usefullness of short-circuit evaluation is parsing through a large csv file with many columns. If one were planning to do a lot of calculations with such a file, it would take a very long time especially if not all the consecutive rows match one's needs. Short circuiting using a conditional is a useful way to cut down the runtime, because that quick check allows the program to skip the calculation step for any rows that do not have the needed information.

5b) Consider the small-step operational semantics for JAVASCRIPTY shown in figures 7, 8, and 9. Does e1 && e2 short circuit? Explain

Given the small-step operational semantics for JAVASCRIPTY shown in figures 7 one can conclude that the expression e1 && e2 does short circuit given the condition that a conversion of e1 to a boolean value (v1) evaluates to false. At this point, rather than evaluating e2, the judgement form says to return v1.

## About
### Introduction
The methodology of School 21 makes sense only if peer-to-peer reviews are done seriously. Please read all guidelines carefully before starting the review.
- Please, stay courteous, polite, respectful and constructive in all communications during this review.
- Highlight possible malfunctions of the work done by the person and take the time to discuss and debate it.
- Keep in mind that sometimes there can be differences in interpretation of the tasks and the scope of features. Please, stay open-minded to the vision of the other.

### Guidelines
- Evaluate only the files that are in src folder on the GIT repository of the student or group.
- Ensure to start reviewing a group project only when the team is present in full.
- Use special flags in the checklist to report, for example, an “empty work” if repository does not contain the work of the student (or group) in the src folder of the develop branch, or “cheat” in case of cheating or if the student (or group) are unable to explain their work at any time during review as well as if one of the points below is not met. However, except for cheating cases, you are encouraged to continue reviewing the project to identify the problems that caused the situation in order to avoid them at the next review.
- Doublecheck that the GIT repository is the one corresponding to the student or the group.
- Meticulously check that nothing malicious has been used to mislead you.
- In controversial cases, remember that the checklist determines only the general order of the check. The final decision on project evaluation remains with the reviewer.
- Check whether the feedback form is filled or not (https://forms.yandex.ru/cloud/641820bf5d2a060d5d1b2b40/)

## Main part
### Creating a database
- The part1.sql script contains the creation of a database and all the tables with the fields described in the task
- The script contains procedures for importing and exporting data for each table from/to files with .csv and .tsv extension
- The separator of the csv file is specified as a parameter of each procedure
- Each table has at least 5 records
- If the data were added by importing from csv or tsv files, these files must be in the repository

### Creating views
- All the views described in the task are contained in scripts starting with part2_ or in part2.sql script
- Come up with at least 3 tests involving different situations. For each test, fill the database with the appropriate data. Data, obtained from each view should be correct, based on the contents of the database, for each of the invented tests
- When uploading information from the datasets folder to the database from files with  _Mini, there are the following lines in the Customers view:
  1	919.22087051893345	"Low" 	76.7075456871345 "Occasionally"   171.304583333333 	2.2332168471668942 	"Medium"   5	1
  3	582.22569577410638	"Low" 	208.94968605324073	"Rarely" 1.23577546296296 	0.00591422502854626 "Low" 1	4

- Since the Purchase history and Periods views are required to compile a Groups view, they do not need a separate check. When uploading information from the datasets folder to the database from files with  _Mini, there are the following lines in the Groups view (the value of the Group_Churn_Rate column may vary slightly):
  1	7	0.66666666666666663 	12.776216932445655	0.984255839689461 	79.170251146703663	1 	0.030023792306903628  0.96122059598970311
  3	1	0.5714285714285714 	0.003255001390036105  0.92231258778923764 	1172.3037277613646	0.5 	0.44917399969379163   0.54075498701499292

### Role model
- The part3.sql script contains all the roles described in the task
- When connecting to a database as an administrator, it is possible to view information from any table and any view
- When connecting to a database as an administrator, it is possible to add and delete information from any table
- When connecting to a database as a visitor, it is possible to view information from any table and any view
- When connecting to a database as a visitor, it is not possible to add and delete information from any table

### Forming personal offers aimed at the growth of the average check
- The part4.sql script contains the function described in the task
- Come up with at least 5 tests involving different situations. For each test, fill the database with the appropriate data. Also try using different values of the function parameters. Data, obtained from each view should be correct, based on the contents of the database, for each of the invented tests
- When uploading information from the datasets folder to the database from files with  _Mini, the function with the next parameters:
  calculation method - 2
  number of transactions - 100
  coefficient of average check increase - 1.15
  maximum churn index - 3
  maximum share of transactions with a discount - 70
  allowable share of margin - 30,
  returns the following data.
  3	669.56 	"Колбаса"    5
  1	1057.1 	"Колбаса"    5
  6	1212.97	"Автомобили" 5
  19  1068.12	"Чипсы"	     5
  5	726.26 	"Бумага"    15

### Forming personal offers, aimed at increasing the frequency of visits
- The part5.sql script contains the function described in the task
- Come up with at least 5 tests involving different situations. For each test, fill the database with the appropriate data. Also try using different values of the function parameters. Data, obtained from each view should be correct, based on the contents of the database, for each of the invented tests
- When uploading information from the datasets folder to the database from files with  _Mini, the function with the next parameters:
  first date of the period - 18.08.2022 00:00:00
  last date of the period - 18.08.2022 00:00:00
  added number of transactions - 1
  maximum churn index - 3
  maximum share of transactions with a discount - 70
  allowable share of margin - 30,
  returns the following data.
  1	2022-08-18T00:00:00.0000000 2022-08-18T00:00:00.0000000   1	"Колбаса"  5
  3	2022-08-18T00:00:00.0000000 2022-08-18T00:00:00.0000000   1	"Колбаса"  5
  6	2022-08-18T00:00:00.0000000 2022-08-18T00:00:00.0000000   1	"Автомобили" 	5
  19   2022-08-18T00:00:00.0000000 2022-08-18T00:00:00.0000000   1	"Чипсы"	5

### Forming personal offers aimed at cross-selling
- The part6.sql script contains the function described in the task
- Come up with at least 5 tests involving different situations. For each test, fill the database with the appropriate data. Also try using different values of the function parameters. Data, obtained from each view should be correct, based on the contents of the database, for each of the invented tests
- When uploading information from the datasets folder to the database from files with  _Mini, the function with the next parameters:
  number of groups - 5
  maximum churn index - 3
  maximum consumption stability index - 0.5
  maximum SKU share - 100
  allowable margin share - 30,
  returns the following data.
  5	"Kerton Бензин АИ-95 Поездка"        15
  11  "Heipz GmbH Ручка шариковая Ромашка"  5

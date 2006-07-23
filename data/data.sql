INSERT INTO categories VALUES (1,'Vegetables',-1);
INSERT INTO categories VALUES (2,'Meat',-1);
INSERT INTO categories VALUES (3,'Fish',-1);
INSERT INTO categories VALUES (4,'Sweets',-1);
INSERT INTO categories VALUES (5,'Starters',-1);
INSERT INTO categories VALUES (6,'Main Dishes',-1);
INSERT INTO categories VALUES (7,'Desserts',-1);
INSERT INTO categories VALUES (8,'Drinks',-1);
INSERT INTO categories VALUES (9,'Pasta',-1);
INSERT INTO categories VALUES (10,'Soups',-1);
INSERT INTO units VALUES (1,'kilogram','kg','kilograms','kg',1);
INSERT INTO units VALUES (2,'gram','g','grams','g',1);
INSERT INTO units VALUES (3,'liter','L','liters','L',2);
INSERT INTO units VALUES (4,'millileter','mL','milliliters','mL',2);
INSERT INTO units VALUES (5,'pound','lb','pounds','lbs',1);
INSERT INTO units VALUES (6,'pint','pt','pints','pt',2);
INSERT INTO units VALUES (7,'unit',NULL,'units',NULL,0);
INSERT INTO units VALUES (8,'tablespoon','tbsp','tablespoons','tbsp',2);
INSERT INTO units VALUES (9,'dash',NULL,'dashes',NULL,0);
INSERT INTO units VALUES (10,'to taste',NULL,'to taste',NULL,0);
INSERT INTO units VALUES (11,'fluid ounce','fl oz','fluid ounces','fl oz',2);
INSERT INTO units VALUES (12,'clove',NULL,'cloves',NULL,0);
INSERT INTO units VALUES (13,'cubic centimeter','cc','cubic centimeters','cc',2);
INSERT INTO units VALUES (14,'bunch',NULL,'bunches',NULL,0);
INSERT INTO units VALUES (15,'cup','c','cups','c',2);
INSERT INTO units VALUES (16,'to taste',NULL,'to taste',NULL,0);
INSERT INTO units VALUES (17,'little',NULL,'little',NULL,0);
INSERT INTO units VALUES (18,'stick',NULL,'sticks',NULL,0);
INSERT INTO units VALUES (19,'teaspoon','tsp','teaspoons','tsp',2);
INSERT INTO units VALUES (20,'quart','qt','quarts','qt',2);
INSERT INTO units VALUES (21,'gallon','gal','gallons','gal',2);
INSERT INTO units VALUES (22,'ounce','oz','ounces','oz',1);
INSERT INTO units VALUES (23,'square','sq','squares','sq',0);
INSERT INTO units VALUES (24,'bottle',NULL,'bottles',NULL,0);
INSERT INTO units VALUES (25,'',NULL,'',NULL,0);
INSERT INTO rating_criteria VALUES (1,'Overall');
INSERT INTO rating_criteria VALUES (2,'Taste');
INSERT INTO rating_criteria VALUES (3,'Appearance');
INSERT INTO rating_criteria VALUES (4,'Originality');
INSERT INTO rating_criteria VALUES (5,'Ease of Preparation');
INSERT INTO units_conversion VALUES(1,2,1000);
INSERT INTO units_conversion VALUES(2,1,0.001);
INSERT INTO units_conversion VALUES(3,4,1000);
INSERT INTO units_conversion VALUES(4,3,0.001);
INSERT INTO units_conversion VALUES(5,1,0.454);
INSERT INTO units_conversion VALUES(1,5,2.20264);
INSERT INTO units_conversion VALUES(6,3,0.473);
INSERT INTO units_conversion VALUES(3,6,2.11416);
INSERT INTO units_conversion VALUES(8,4,14.786);
INSERT INTO units_conversion VALUES(4,8,0.0676315);
INSERT INTO units_conversion VALUES(3,8,67.628);
INSERT INTO units_conversion VALUES(8,3,0.0147868);
INSERT INTO units_conversion VALUES(13,4,1);
INSERT INTO units_conversion VALUES(4,13,1);
INSERT INTO units_conversion VALUES(13,3,0.001);
INSERT INTO units_conversion VALUES(3,13,1000);
INSERT INTO units_conversion VALUES(8,13,14.786);
INSERT INTO units_conversion VALUES(13,8,0.0676315);
INSERT INTO units_conversion VALUES(8,6,0.03125);
INSERT INTO units_conversion VALUES(6,8,32);
INSERT INTO units_conversion VALUES(6,4,473.176);
INSERT INTO units_conversion VALUES(4,6,0.00211338);
INSERT INTO units_conversion VALUES(6,13,473.176);
INSERT INTO units_conversion VALUES(13,6,0.00211338);
INSERT INTO units_conversion VALUES(6,15,2);
INSERT INTO units_conversion VALUES(15,6,0.5);
INSERT INTO units_conversion VALUES(2,5,0.00220264);
INSERT INTO units_conversion VALUES(5,2,454);
INSERT INTO units_conversion VALUES(3,15,4.22833);
INSERT INTO units_conversion VALUES(15,3,0.2365);
INSERT INTO units_conversion VALUES(8,15,0.0625);
INSERT INTO units_conversion VALUES(15,8,16);
INSERT INTO units_conversion VALUES(4,15,0.00422676);
INSERT INTO units_conversion VALUES(15,4,236.588);
INSERT INTO units_conversion VALUES(13,15,0.00422676);
INSERT INTO units_conversion VALUES(15,13,236.588);
INSERT INTO units_conversion VALUES(20,6,2);
INSERT INTO units_conversion VALUES(6,20,0.5);
INSERT INTO units_conversion VALUES(3,20,1.05708);
INSERT INTO units_conversion VALUES(20,3,0.946);
INSERT INTO units_conversion VALUES(8,20,0.015625);
INSERT INTO units_conversion VALUES(20,8,64);
INSERT INTO units_conversion VALUES(4,20,0.00105669);
INSERT INTO units_conversion VALUES(20,4,946.352);
INSERT INTO units_conversion VALUES(13,20,0.00105669);
INSERT INTO units_conversion VALUES(20,13,946.352);
INSERT INTO units_conversion VALUES(15,20,0.25);
INSERT INTO units_conversion VALUES(20,15,4);
INSERT INTO units_conversion VALUES(21,20,4);
INSERT INTO units_conversion VALUES(20,21,0.25);
INSERT INTO units_conversion VALUES(6,21,0.125);
INSERT INTO units_conversion VALUES(21,6,8);
INSERT INTO units_conversion VALUES(3,21,0.264271);
INSERT INTO units_conversion VALUES(21,3,3.784);
INSERT INTO units_conversion VALUES(8,21,0.00390625);
INSERT INTO units_conversion VALUES(21,8,256);
INSERT INTO units_conversion VALUES(4,21,0.000264172);
INSERT INTO units_conversion VALUES(21,4,3785.41);
INSERT INTO units_conversion VALUES(13,21,0.000264172);
INSERT INTO units_conversion VALUES(21,13,3785.41);
INSERT INTO units_conversion VALUES(15,21,0.0625);
INSERT INTO units_conversion VALUES(21,15,16);
INSERT INTO units_conversion VALUES(5,22,16);
INSERT INTO units_conversion VALUES(22,5,0.0625);
INSERT INTO units_conversion VALUES(1,22,35.2423);
INSERT INTO units_conversion VALUES(22,1,0.028375);
INSERT INTO units_conversion VALUES(2,22,0.0352734);
INSERT INTO units_conversion VALUES(22,2,28.35);
INSERT INTO units_conversion VALUES(8,19,3);
INSERT INTO units_conversion VALUES(19,8,0.333333);
INSERT INTO units_conversion VALUES(4,19,0.202895);
INSERT INTO units_conversion VALUES(19,4,4.92866);
INSERT INTO units_conversion VALUES(3,19,202.884);
INSERT INTO units_conversion VALUES(19,3,0.00492893);
INSERT INTO units_conversion VALUES(13,19,0.202895);
INSERT INTO units_conversion VALUES(19,13,4.92866);
INSERT INTO units_conversion VALUES(6,19,96.0001);
INSERT INTO units_conversion VALUES(19,6,0.0104167);
INSERT INTO units_conversion VALUES(15,19,48);
INSERT INTO units_conversion VALUES(19,15,0.0208333);
INSERT INTO units_conversion VALUES(20,19,192);
INSERT INTO units_conversion VALUES(19,20,0.00520833);
INSERT INTO units_conversion VALUES(21,19,768.001);
INSERT INTO units_conversion VALUES(19,21,0.00130208);
INSERT INTO units_conversion VALUES(24,4,29.574);
INSERT INTO units_conversion VALUES(4,24,0.0338135);
INSERT INTO units_conversion VALUES(3,24,33.8135);
INSERT INTO units_conversion VALUES(24,3,0.029574);
INSERT INTO units_conversion VALUES(8,24,0.499967);
INSERT INTO units_conversion VALUES(24,8,2.00013);
INSERT INTO units_conversion VALUES(13,24,0.0338135);
INSERT INTO units_conversion VALUES(24,13,29.574);
INSERT INTO units_conversion VALUES(6,24,15.9997);
INSERT INTO units_conversion VALUES(24,6,0.0625011);
INSERT INTO units_conversion VALUES(15,24,7.99986);
INSERT INTO units_conversion VALUES(24,15,0.125002);
INSERT INTO units_conversion VALUES(20,24,31.9994);
INSERT INTO units_conversion VALUES(24,20,0.0312506);
INSERT INTO units_conversion VALUES(21,24,127.998);
INSERT INTO units_conversion VALUES(24,21,0.00781262);
INSERT INTO units_conversion VALUES(19,24,0.166655);
INSERT INTO units_conversion VALUES(24,19,6.00042);


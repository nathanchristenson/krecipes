INSERT INTO author_list VALUES (1,1);
INSERT INTO author_list VALUES (2,2);
INSERT INTO author_list VALUES (3,3);
INSERT INTO author_list VALUES (4,4);
INSERT INTO authors VALUES (1,'Adriaan de Groot');
INSERT INTO authors VALUES (2,'Ian Reinhart Geiser');
INSERT INTO authors VALUES (3,'Ravikiran Rajagopal');
INSERT INTO authors VALUES (4,'Unai Garro');
INSERT INTO categories VALUES (1,'Vegetables');
INSERT INTO categories VALUES (2,'Meat',-1);
INSERT INTO categories VALUES (3,'Fish',-1);
INSERT INTO categories VALUES (4,'Sweets',-1);
INSERT INTO categories VALUES (5,'Starters',-1);
INSERT INTO categories VALUES (6,'Main Dishes',-1);
INSERT INTO categories VALUES (7,'Desserts',-1);
INSERT INTO categories VALUES (8,'Drinks',-1);
INSERT INTO categories VALUES (9,'Pasta',-1);
INSERT INTO categories VALUES (10,'Soups',-1);
INSERT INTO category_list VALUES (1,1);
INSERT INTO category_list VALUES (1,9);
INSERT INTO category_list VALUES (2,10);
INSERT INTO category_list VALUES (3,2);
INSERT INTO category_list VALUES (4,7);
INSERT INTO category_list VALUES (4,4);
INSERT INTO ingredient_list VALUES (1,1,200,2,-1,1);
INSERT INTO ingredient_list VALUES (1,2,1,7,-1,2);
INSERT INTO ingredient_list VALUES (1,3,150,2,-1,3);
INSERT INTO ingredient_list VALUES (1,4,100,4,-1,4);
INSERT INTO ingredient_list VALUES (1,5,2,8,-1,5);
INSERT INTO ingredient_list VALUES (1,6,1,8,-1,6);
INSERT INTO ingredient_list VALUES (1,7,1,8,-1,7);
INSERT INTO ingredient_list VALUES (1,8,1,9,-1,8);
INSERT INTO ingredient_list VALUES (1,11,1,9,-1,9);
INSERT INTO ingredient_list VALUES (1,12,1,9,-1,10);
INSERT INTO ingredient_list VALUES (1,9,1,10,-1,11);
INSERT INTO ingredient_list VALUES (1,10,1,11,-1,12);
INSERT INTO ingredient_list VALUES (1,13,100,2,-1,13);
INSERT INTO ingredient_list VALUES (1,14,2,7,-1,14);
INSERT INTO ingredient_list VALUES (2,20,6,13,-1,1);
INSERT INTO ingredient_list VALUES (2,19,0.25,12,-1,2);
INSERT INTO ingredient_list VALUES (2,18,3,12,-1,3);
INSERT INTO ingredient_list VALUES (2,17,1,7,-1,4);
INSERT INTO ingredient_list VALUES (2,16,6,8,-1,5);
INSERT INTO ingredient_list VALUES (2,15,2,5,-1,6);
INSERT INTO ingredient_list VALUES (3,21,800,2,-1,1);
INSERT INTO ingredient_list VALUES (3,22,3,14,-1,2);
INSERT INTO ingredient_list VALUES (3,23,2,15,-1,3);
INSERT INTO ingredient_list VALUES (3,24,0.5,5,-1,4);
INSERT INTO ingredient_list VALUES (3,25,0.5,8,-1,5);
INSERT INTO ingredient_list VALUES (3,31,0.25,8,-1,6);
INSERT INTO ingredient_list VALUES (3,27,1,8,-1,7);
INSERT INTO ingredient_list VALUES (3,28,5,2,-1,8);
INSERT INTO ingredient_list VALUES (3,29,1,7,-1,9);
INSERT INTO ingredient_list VALUES (3,30,1,10,-1,10);
INSERT INTO ingredient_list VALUES (3,32,1,17,-1,11);
INSERT INTO ingredient_list VALUES (3,33,1,17,-1,12);
INSERT INTO ingredient_list VALUES (3,34,1,17,-1,13);
INSERT INTO ingredient_list VALUES (4,16,185,2,-1,1);
INSERT INTO ingredient_list VALUES (4,35,425,2,-1,2);
INSERT INTO ingredient_list VALUES (4,37,250,2,-1,3);
INSERT INTO ingredient_list VALUES (4,38,7,7,-1,4);
INSERT INTO ingredient_list VALUES (4,39,1,7,-1,5);
INSERT INTO ingredient_list VALUES (4,40,300,2,-1,6);
INSERT INTO ingredient_list VALUES (4,41,1,18,-1,7);
INSERT INTO ingredient_list VALUES (4,42,1,7,-1,8);
INSERT INTO ingredient_list VALUES (4,43,100,2,-1,9);
INSERT INTO ingredient_list VALUES (4,44,100,2,-1,10);
INSERT INTO ingredient_list VALUES (4,36,0.5,3,-1,11);
INSERT INTO ingredient_properties VALUES (1,'Energy','kcal');
INSERT INTO ingredient_properties VALUES (2,'Proteins','g');
INSERT INTO ingredient_properties VALUES (3,'Fiber','g');
INSERT INTO ingredient_properties VALUES (4,'Calcium','g');
INSERT INTO ingredient_properties VALUES (5,'Fat','g');
INSERT INTO ingredients VALUES (1,'fusili pasta');
INSERT INTO ingredients VALUES (2,'zucchini');
INSERT INTO ingredients VALUES (3,'mushrooms');
INSERT INTO ingredients VALUES (4,'cream');
INSERT INTO ingredients VALUES (5,'red wine');
INSERT INTO ingredients VALUES (6,'dill weed');
INSERT INTO ingredients VALUES (7,'horseradish');
INSERT INTO ingredients VALUES (8,'parsley');
INSERT INTO ingredients VALUES (9,'pepper');
INSERT INTO ingredients VALUES (10,'olive oil');
INSERT INTO ingredients VALUES (11,'thyme');
INSERT INTO ingredients VALUES (12,'chives');
INSERT INTO ingredients VALUES (13,'grated cheese');
INSERT INTO ingredients VALUES (14,'tomatoes');
INSERT INTO ingredients VALUES (15,'carrot');
INSERT INTO ingredients VALUES (16,'butter');
INSERT INTO ingredients VALUES (17,'onion');
INSERT INTO ingredients VALUES (18,'garlic');
INSERT INTO ingredients VALUES (19,'ginger');
INSERT INTO ingredients VALUES (20,'vegetable stock');
INSERT INTO ingredients VALUES (21,'minced lamb');
INSERT INTO ingredients VALUES (22,'spring onions');
INSERT INTO ingredients VALUES (23,'chopped leaf spinnach');
INSERT INTO ingredients VALUES (24,'green peas');
INSERT INTO ingredients VALUES (25,'crushed cilantro (coriander) seeds');
INSERT INTO ingredients VALUES (26,'crushed cumin seeds');
INSERT INTO ingredients VALUES (27,'lemon juice');
INSERT INTO ingredients VALUES (28,'mustard seeds');
INSERT INTO ingredients VALUES (29,'Roma tomato');
INSERT INTO ingredients VALUES (30,'vinegar');
INSERT INTO ingredients VALUES (31,'crushed cinnamon bark');
INSERT INTO ingredients VALUES (32,'oil');
INSERT INTO ingredients VALUES (33,'salt');
INSERT INTO ingredients VALUES (34,'crushed black pepper');
INSERT INTO ingredients VALUES (35,'flour');
INSERT INTO ingredients VALUES (36,'milk');
INSERT INTO ingredients VALUES (37,'sugar');
INSERT INTO ingredients VALUES (38,'egg yolks');
INSERT INTO ingredients VALUES (39,'eggs');
INSERT INTO ingredients VALUES (40,'icing sugar');
INSERT INTO ingredients VALUES (41,'cinamon');
INSERT INTO ingredients VALUES (42,'vanilla pods');
INSERT INTO ingredients VALUES (43,'almonds');
INSERT INTO ingredients VALUES (44,'currants');
INSERT INTO recipes VALUES (1,'Kaas, Dille, Eten',2,'Put on 1.5l of water, salted, on to boil. Slice the zucchini in thin slices (about 3mm thick). Chop the mushrooms. Heat olive oil in a heavy iron skillet, add zucchini and fry on high heat for 3 min or so, then add mushrooms and wine, reduce heat, and allow to fry/simmer/turn brown for another 5 minutes or so. By now the water for the pasta should be boiling. Add the pasta and let it cook for the 10 minutes or so it needs to become "al dente". Add the cream, dill, horseradish, herbs and pepper to the zucchini and mushroom mix, and allow to simmer while the pasta cooks. Drain the pasta, add it to the vegetables, mix well.
Serve topped with cheese and with sliced tomato around the edge of the plate.
',NULL);
INSERT INTO recipes VALUES (2,'Carrot Soup',2,'Chop the Onion, Garlic and Ginger as fine as possible, then satue in the butter. Don’t let the onion get to dark, just saute until soft.
 
Peel and cut up the carrots into 1inch chunks so they are manageable.
 
Then add in the vegitable stocj, and carrots. Simmer for about 45minutes. When the carrots are soft let the mixture cool.

Place the carrot chunks and broth into a blender and puree it. When the entire mixture is smooth its ready to eat. You can also add 2T lemon juice and/or a dash of curry powder for taste, but its great without it too.

The soup is great hot or cold and is vegan friendly.',NULL);
INSERT INTO recipes VALUES (3,'Lamb Stuffing',1,'Chop the spring onions (from the green leaves all the way close to the root) into 1cm long pieces. Dice the tomato if you use it. In a sautee-pan, add a little oil, the mustard seeds, and eat it. When the mustard seeds start popping, add the chooped spring onions, thawed green peas, and sautee for about 2 minutes. Then, add the spinach, tomato and cilantro powder, and sautee until almost dry. Add thawed minced lamb, a cup of water and stir to make the mixture almost homogeneous. Add cumin powder, cinnamon and salt, and stir thoroughly. Let it simmer for a while until most of the water is gone. Then sprinkle crushed black pepper to required degree of spiciness. Add lemon juice (and vinegar for extra tang) and stir. The pepper should absorb all the remaining water. Stir vigorously for about 30 seconds and remove from heat.

This makes great stuffing for pitas. Personally, if I have the time, I add the cooked stuffing above to wet rice flour, and steam to obtain flavoured rice cakes, which is consumed by itself or (usually) with coconut chutney.

Note: Be careful adding the cumin and cinnamon. They tend to clump, and you should avoid that be adding them little by little while strirring the mixture.',NULL);
INSERT INTO recipes VALUES (4,'Gateau Basque / Pastel Vasco',4,'First, we need to make the dough: place in a mixing bowl 375g of the flour and make a hole in the middle, where you can place the butter slightly soft, the icing (or normal) sugar, 3 egg yolks, the egg, and 375g flour. Mix all these properly until you get something quite consistant.  And leave it in the fridge for at least 1/2 an hour, covered with cling film.

In the mean time, in order to make some cream, put the milk boiling in a saucepan, and add the cinamon and the vanilla pod. Midwhile, mix in a bowl the 150 g of the sugar, the rest of the flour (50g), and the 4 egg yolks that are left. Once the milk is boiling, remove the cinamon and the vanilla pod and add this mixture to the milk. Keep going on mixing continuously until the cream gets quite thick, and once it starts boiling add the almonds, previously grounded, 100 g of sugar which is left, and the currants. Leave this mixture in the fridge for 1/2 an hour.

Once these two things are done, get a mould ready for baking spreading a bit of butter and then flour so that the cake won''t stick to the mould.

Now, put a thin (less than 5mm) layer of the dough covering the bottom and side parts of the mould, and fill it in with the cream, and cover on top with the rest of the dough in the same way.

Paint the cake''s top part with a bit of whisked egg, and put it in the oven at 190�C for around 30 mins. Et voil� you have a delicious sweet cake.
',NULL);
INSERT INTO unit_list VALUES (1,2);
INSERT INTO unit_list VALUES (2,7);
INSERT INTO unit_list VALUES (3,2);
INSERT INTO unit_list VALUES (4,4);
INSERT INTO unit_list VALUES (5,8);
INSERT INTO unit_list VALUES (6,8);
INSERT INTO unit_list VALUES (7,8);
INSERT INTO unit_list VALUES (8,9);
INSERT INTO unit_list VALUES (9,10);
INSERT INTO unit_list VALUES (10,11);
INSERT INTO unit_list VALUES (11,9);
INSERT INTO unit_list VALUES (12,9);
INSERT INTO unit_list VALUES (13,2);
INSERT INTO unit_list VALUES (14,7);
INSERT INTO unit_list VALUES (15,5);
INSERT INTO unit_list VALUES (16,8);
INSERT INTO unit_list VALUES (17,7);
INSERT INTO unit_list VALUES (18,12);
INSERT INTO unit_list VALUES (19,4);
INSERT INTO unit_list VALUES (19,12);
INSERT INTO unit_list VALUES (20,13);
INSERT INTO unit_list VALUES (21,2);
INSERT INTO unit_list VALUES (22,14);
INSERT INTO unit_list VALUES (23,15);
INSERT INTO unit_list VALUES (24,5);
INSERT INTO unit_list VALUES (25,8);
INSERT INTO unit_list VALUES (26,8);
INSERT INTO unit_list VALUES (27,8);
INSERT INTO unit_list VALUES (28,2);
INSERT INTO unit_list VALUES (29,7);
INSERT INTO unit_list VALUES (31,8);
INSERT INTO unit_list VALUES (30,10);
INSERT INTO unit_list VALUES (32,17);
INSERT INTO unit_list VALUES (33,17);
INSERT INTO unit_list VALUES (34,17);
INSERT INTO unit_list VALUES (16,2);
INSERT INTO unit_list VALUES (35,2);
INSERT INTO unit_list VALUES (36,3);
INSERT INTO unit_list VALUES (37,2);
INSERT INTO unit_list VALUES (38,7);
INSERT INTO unit_list VALUES (39,7);
INSERT INTO unit_list VALUES (40,2);
INSERT INTO unit_list VALUES (41,18);
INSERT INTO unit_list VALUES (42,7);
INSERT INTO unit_list VALUES (43,2);
INSERT INTO unit_list VALUES (44,2);
INSERT INTO units VALUES (1,'Kg');
INSERT INTO units VALUES (2,'g');
INSERT INTO units VALUES (3,'l');
INSERT INTO units VALUES (4,'ml');
INSERT INTO units VALUES (5,'lb');
INSERT INTO units VALUES (6,'pints');
INSERT INTO units VALUES (7,'units');
INSERT INTO units VALUES (8,'tbsp');
INSERT INTO units VALUES (9,'dash');
INSERT INTO units VALUES (10,'to taste');
INSERT INTO units VALUES (11,'n/a');
INSERT INTO units VALUES (12,'cloves');
INSERT INTO units VALUES (13,'cc');
INSERT INTO units VALUES (14,'bunches');
INSERT INTO units VALUES (15,'cups');
INSERT INTO units VALUES (16,'tiny quantity to tas');
INSERT INTO units VALUES (17,'little');
INSERT INTO units VALUES (18,'sticks');
INSERT INTO units_conversion VALUES (1,2,1000);
INSERT INTO units_conversion VALUES (2,1,0.001);
INSERT INTO units_conversion VALUES (3,4,1000);
INSERT INTO units_conversion VALUES (4,3,0.001);
INSERT INTO units_conversion VALUES (1,5,0.454);
INSERT INTO units_conversion VALUES (5,1,2.20264);
INSERT INTO units_conversion VALUES (6,3,0.473);
INSERT INTO units_conversion VALUES (3,6,2.11416);
INSERT INTO units_conversion VALUES (8,4,14.786);
INSERT INTO units_conversion VALUES (4,8,0.0676315);
INSERT INTO units_conversion VALUES (8,3,67.628);
INSERT INTO units_conversion VALUES (3,8,0.0147868);
INSERT INTO units_conversion VALUES (13,4,1);
INSERT INTO units_conversion VALUES (4,13,1);
INSERT INTO units_conversion VALUES (13,3,0.001);
INSERT INTO units_conversion VALUES (3,13,1000);
INSERT INTO units_conversion VALUES (8,13,14.786);
INSERT INTO units_conversion VALUES (13,8,0.0676315);
INSERT INTO units_conversion VALUES (8,6,0.03125);
INSERT INTO units_conversion VALUES (6,8,32);
INSERT INTO units_conversion VALUES (6,4,473.176);
INSERT INTO units_conversion VALUES (4,6,0.00211338);
INSERT INTO units_conversion VALUES (6,13,473.176);
INSERT INTO units_conversion VALUES (13,6,0.00211338);


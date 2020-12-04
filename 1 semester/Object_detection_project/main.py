import template_matching as tm

points = tm.findClickPositions('albion_cabbage.jpg', 'albion_farm.jpg', debug_mode='points')
print(points)
points = tm.findClickPositions('albion_turnip.jpg', 'albion_farm.jpg',
                            threshold=0.70, debug_mode='rectangles')
print(points)
print('Done.')
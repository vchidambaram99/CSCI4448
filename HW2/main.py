# Valliappan Chidambaram
# 2/10/19
# CSCI4448 HW1

class Shape():
	def __init__(self,z=0):
		self._z = z
	@property
	def z(self):
		return self._z
	@z.setter
	def z(self,value):
		self._z = value
	def display(self):
		print("z: {}, Shape".format(self._z))

class Circle(Shape):
	def __init__(self,pos,r,z=0):
		self._z = z
		self._pos = pos
		self._r = r
	@property
	def pos(self):
		return self._pos
	@pos.setter
	def pos(self,value):
		self._pos = value
	@property
	def r(self):
		return self._r
	@r.setter
	def r(self,value):
		assert (r>=0), "Radius must be nonnegative"
		self._r = value
	def display(self):
		print("z: {}, Circle with radius {} and center {}".format(self._z,self._r,self._pos))

class Triangle(Shape):
	def __init__(self,points,z=0):
		self._z = z
		self.points = points
	@property
	def points(self):
		return self._points
	@points.setter
	def points(self,value):
		assert len(value)==3, "Triangles only have 3 points"
		self._points = value
	def display(self):
		print("z: {}, Triangle with points at {}, {}, and {}".format(self._z,self._points[0],self._points[1],self._points[2]))

class Rectangle(Shape):
	def __init__(self,ul,br,z=0):
		self._z = z
		self.corners = (ul,br)
	@property
	def corners(self):
		return (self._ul,self._br)
	@corners.setter
	def corners(self,value):
		assert len(value)==2, "Only upper left and bottom right corners"
		assert value[0][0]<=value[1][0], "Upper left x must be <= lower right x"
		assert value[0][1]>=value[1][1], "Upper left y must be >= lower right y"
		self._ul = value[0]
		self._br = value[1]
	def display(self):
		print("z: {}, Rectangle with upper left corner at {}, and lower right corner at {}".format(self._z,self._ul,self._br))

class ShapeList():
	def __init__(self,shapes):
		self._shapes = shapes
	def displayAll(self):
		self._shapes.sort(key=lambda s: s.z)
		for shape in self._shapes:
			shape.display()
	def addShape(self,shape):
		self._shapes.append(shape)

if __name__ == "__main__":
	shapes = ShapeList([Circle((0,0),5,3),Rectangle((-1,1),(1,-1)),Triangle([(0,0),(1,1),(0,2)],4),Circle((2,2),1,2),Triangle([(10,10),(15,15),(10,15)],1)])
	shapes.displayAll()

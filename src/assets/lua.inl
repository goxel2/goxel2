/* This file is autogenerated by tools/create_assets.py */

{
	.path = "data/lua/vector3.lua",
	.size = 4624,
	.data = "--------------------------------------------------------------------------------\n--   Copyright (c) 2015 , 蒙占志(topameng) topameng@gmail.com\n--   All rights reserved.\n--\n--   Use, modification and distribution are subject to the \"New BSD License\"\n--   as listed at <url: http://www.opensource.org/licenses/bsd-license.php>.\n--------------------------------------------------------------------------------\n\nlocal acos	= math.acos\nlocal sqrt 	= math.sqrt\nlocal max 	= math.max\nlocal min 	= math.min\nlocal clamp = math.clamp\nlocal cos	= math.cos\nlocal sin	= math.sin\nlocal abs	= math.abs\nlocal sign	= math.sign\nlocal setmetatable = setmetatable\nlocal rawset = rawset\nlocal rawget = rawget\n\nlocal rad2Deg = math.rad2Deg\nlocal deg2Rad = math.deg2Rad\n\nVector3 = {	\n	class = \"Vector3\",\n}\n\nlocal fields = {}\n\nsetmetatable(Vector3, Vector3)\n\nVector3.__index = function(t,k)\n	local var = rawget(Vector3, k)\n	\n	if var == nil then							\n		var = rawget(fields, k)\n		\n		if var ~= nil then\n			return var(t)				\n		end		\n	end\n	\n	return var\nend\n\nVector3.__call = function(t,x,y,z)\n	return Vector3.New(x,y,z)\nend\n\nfunction Vector3.New(x, y, z)\n	local v = {x = x or 0, y = y or 0, z = z or 0}		\n	setmetatable(v, Vector3)		\n	return v\nend\n	\nfunction Vector3:Set(x,y,z)	\n	self.x = x or 0\n	self.y = y or 0\n	self.z = z or 0\nend\n\nfunction Vector3:Get()	\n	return self.x, self.y, self.z	\nend\n\nfunction Vector3:Clone()\n	return Vector3.New(self.x, self.y, self.z)\nend\n\nfunction Vector3.Distance(va, vb)\n	return sqrt((va.x - vb.x)^2 + (va.y - vb.y)^2 + (va.z - vb.z)^2)\nend\n\nfunction Vector3.Max(lhs, rhs)\n	return Vector3.New(max(lhs.x, rhs.x), max(lhs.y, rhs.y), max(lhs.z, rhs.z))\nend\n\nfunction Vector3.Min(lhs, rhs)\n	return Vector3.New(min(lhs.x, rhs.x), min(lhs.y, rhs.y), min(lhs.z, rhs.z))\nend\n\nfunction Vector3.Cross(lhs, rhs)\n	local x = lhs.y * rhs.z - lhs.z * rhs.y\n	local y = lhs.z * rhs.x - lhs.x * rhs.z\n	local z = lhs.x * rhs.y - lhs.y * rhs.x\n	return Vector3.New(x,y,z)	\nend\n\nfunction Vector3:Equals(other)\n	return self.x == other.x and self.y == other.y and self.z == other.z\nend\n\nfunction Vector3:Mul(q)\n	if type(q) == \"number\" then\n		self.x = self.x * q\n		self.y = self.y * q\n		self.z = self.z * q\n	else\n		self:MulQuat(q)\n	end\n	\n	return self\nend\n\nfunction Vector3:Div(d)\n	self.x = self.x / d\n	self.y = self.y / d\n	self.z = self.z / d\n	\n	return self\nend\n\nfunction Vector3:Add(vb)\n	self.x = self.x + vb.x\n	self.y = self.y + vb.y\n	self.z = self.z + vb.z\n	\n	return self\nend\n\nfunction Vector3:Sub(vb)\n	self.x = self.x - vb.x\n	self.y = self.y - vb.y\n	self.z = self.z - vb.z\n	\n	return self\nend\n\nfunction Vector3:MulQuat(quat)	   \n	local num 	= quat.x * 2\n	local num2 	= quat.y * 2\n	local num3 	= quat.z * 2\n	local num4 	= quat.x * num\n	local num5 	= quat.y * num2\n	local num6 	= quat.z * num3\n	local num7 	= quat.x * num2\n	local num8 	= quat.x * num3\n	local num9 	= quat.y * num3\n	local num10 = quat.w * num\n	local num11 = quat.w * num2\n	local num12 = quat.w * num3\n	\n	local x = (((1 - (num5 + num6)) * self.x) + ((num7 - num12) * self.y)) + ((num8 + num11) * self.z)\n	local y = (((num7 + num12) * self.x) + ((1 - (num4 + num6)) * self.y)) + ((num9 - num10) * self.z)\n	local z = (((num8 - num11) * self.x) + ((num9 + num10) * self.y)) + ((1 - (num4 + num5)) * self.z)\n	\n	self:Set(x, y, z)	\n	return self\nend\n\nVector3.__tostring = function(self)\n	return \"[\"..self.x..\",\"..self.y..\",\"..self.z..\"]\"\nend\n\nVector3.__div = function(va, d)\n	return Vector3.New(va.x / d, va.y / d, va.z / d)\nend\n\nVector3.__mul = function(va, d)\n	if type(d) == \"number\" then\n		return Vector3.New(va.x * d, va.y * d, va.z * d)\n	else\n		local vec = va:Clone()\n		vec:MulQuat(d)\n		return vec\n	end	\nend\n\nVector3.__add = function(va, vb)\n	return Vector3.New(va.x + vb.x, va.y + vb.y, va.z + vb.z)\nend\n\nVector3.__sub = function(va, vb)\n	return Vector3.New(va.x - vb.x, va.y - vb.y, va.z - vb.z)\nend\n\nVector3.__unm = function(va)\n	return Vector3.New(-va.x, -va.y, -va.z)\nend\n\nVector3.__eq = function(a,b)\n	local v = a - b\n	local delta = v:SqrMagnitude()\n	return delta < 1e-10\nend\n\n-- Direction                                     x  y  z\nfields.up 		= function() return Vector3.New( 0, 0, 1) end\nfields.down 	= function() return Vector3.New( 0, 0, 0) end\nfields.right	= function() return Vector3.New( 1, 0, 0) end\nfields.left		= function() return Vector3.New(-1, 0, 0) end\nfields.forward 	= function() return Vector3.New( 0, 1, 0) end\nfields.back		= function() return Vector3.New( 0,-1, 0) end\nfields.zero		= function() return Vector3.New( 0, 0, 0) end\n\nfields.magnitude 	= Vector3.Magnitude\nfields.normalized 	= Vector3.Normalize\nfields.sqrMagnitude = Vector3.SqrMagnitude\n"
},




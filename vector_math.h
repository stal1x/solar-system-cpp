/*
 *  math.h
 *  
 *
 *  Created by Jason Hsu on 10/7/09.
 *  Copyright 2009. All rights reserved.
 *
 */

#include <algorithm>
#include <string>

class Tuple3;
class Point3;
class Vector3;
class Color;

class Tuple3
{
public:
    /** The x coordinate of the Tuple3. */
	double x;
    /** The y coordinate of the Tuple3. */
    double y;
    /** The z coordinate of the Tuple3. */
    double z;
	
	
    /**
     * Default constructor. Uses explicit constructor to create a zero vector.
     */
	Tuple3 ()
    {
        Tuple3(0, 0, 0);
    }
	
	
//    /**
//     * Copy constructor. This constructor simply calls the explicit constructor
//     * with the necessary fields from the input as parameters.
//     * 
//     * @param newTuple The vector to copy.
//     */
//    Tuple3 (Tuple3 newTuple)
//    {
//        Tuple3(newTuple.x, newTuple.y, newTuple.z);
//    }
	
	
    /**
     * The explicit constructor. This is the only constructor with any real code
     * in it. Values should be set here, and any variables that need to be
     * calculated should be done here.
     * 
     * @param newX The x value of the new vector.
     * @param newY The y value of the new vector.
     * @param newZ The z value of the new vector.
     */
    Tuple3 (double newX, double newY, double newZ)
    {
        x = newX;
        y = newY;
        z = newZ;
    }
	
	
    /**
     * Scale this Tuple3 by op1
     * 
     * @param op1 the scale factor
     */
    void scale (double op1)
    {
        x *= op1;
        y *= op1;
        z *= op1;
    }
	
	
    /**
     * Sets this tuple to have the contents of another tuple. Allows quick
     * conversion between points and vectors.
     * 
     * @param inTuple the input tuple
     */
    void set (Tuple3 inTuple)
    {
        x = inTuple.x;
        y = inTuple.y;
        z = inTuple.z;
    }
	
	
    /**
     * Set the value of this Tuple3 to the three input values
     * 
     * @param inX the new X value
     * @param inY the new Y value
     * @param inZ the new Z value
     */
    void set (double inX, double inY, double inZ)
    {
        x = inX;
        y = inY;
        z = inZ;
    }
	
	
    /**
     * @see Object#toString()
     */
    string toString ()
    {
        return "[" + x + "," + y + "," + z + "]";
    }
};

class Point3 : public Tuple3
{
public:
    /**
     * Default constructor. Uses explicit constructor to create a zero vector.
     */
    Point3 () : Tuple3()
	{
	}
	
	
//    /**
//     * Copy constructor. This constructor simply calls the explicit constructor
//     * with the necessary fields from the input as parameters.
//     * 
//     * @param newTuple The Point3 to copy.
//     */
//    Point3 (Point3 newTuple) : Tuple3(newTuple)
//    {
//    }
	
	
    /**
     * The explicit constructor. This is the only constructor with any real code
     * in it. Values should be set here, and any variables that need to be
     * calculated should be done here.
     * 
     * @param newX The x value of the new Point3.
     * @param newY The y value of the new Point3.
     * @param newZ The z value of the new Point3.
     */
    Point3 (double newX, double newY, double newZ) : Tuple3(newX, newY, newZ)
    {
    }
	
	
    /**
     * Returns the squared distance from this Point3 to other
     * 
     * @param other another point
     * @return the squared distance from this point to the other point
     */
    double distanceSquared (Point3 other)
    {
        double dx = (x - other.x);
        double dy = (y - other.y);
        double dz = (z - other.z);
        return dx * dx + dy * dy + dz * dz;
    }
	
	
    /**
     * Returns the distance from this Point3 to other
     * 
     * @param other another point
     * @return the distance
     */
    double distance (Point3 other)
    {
        return Math.sqrt(distanceSquared(other));
    }
	
	
    /**
     * Add a Vector3 to this Point3
     * 
     * @param op1 the Vector3 to add
     */
    void add (Vector3 vector)
    {
        add(*this, vector);
    }
	
	
    /**
     * Add a Vector3 to a Point3 and store the result in this Point3
     * 
     * @param point the input point
     * @param vector the input vector
     */
    void add (Point3 point, Vector3 vector)
    {
        x = vector.x + point.x;
        y = vector.y + point.y;
        z = vector.z + point.z;
    }
	
	
    /**
     * Subtract a Vector3 to this Point3
     * 
     * @param op1 the Vector3 to substract
     */
    void sub (Vector3 vector)
    {
        sub(*this, vector);
    }
	
	
    /**
     * Subtract a Vector3 from a Point3 and store the result in this Point3
     * 
     * @param point the input point
     * @param vector the input vector
     */
    void sub (Point3 point, Vector3 vector)
    {
        x = point.x - vector.x;
        y = point.y - vector.y;
        z = point.z - vector.z;
    }
	
	
    /**
     * Add a scaled multiple of a Vector3 to this Point3
     * 
     * @param scale the input scale
     * @param vector the input vector
     */
    void scaleAdd (double scale, Vector3 vector)
    {
        x += scale * vector.x;
        y += scale * vector.y;
        z += scale * vector.z;
    }
};

class Vector3 : public Tuple3
{
public:
    /**
     * Default constructor. Uses explicit constructor to create a zero vector.
     */
    Vector3 () : Tuple3()
    {
    }
	
//	
//    /**
//     * Copy constructor. This constructor simply calls the explicit constructor
//     * with the necessary fields from the input as parameters.
//     * 
//     * @param newTuple The vector to copy.
//     */
//    Vector3 (Tuple3 newTuple) : Tuple3(newTuple)
//    {
//    }
	
	
    /**
     * The explicit constructor. This is the only constructor with any real code
     * in it. Values should be set here, and any variables that need to be
     * calculated should be done here.
     * 
     * @param newX The x value of the new vector.
     * @param newY The y value of the new vector.
     * @param newZ The z value of the new vector.
     */
    Vector3 (double newX, double newY, double newZ) : Tuple3(newX, newY, newZ)
    {
    }
	
	
    /**
     * Sets this vector to the cross product of op1 and op2
     * 
     * @param op1
     * @param op2
     */
    void cross (Vector3 op1, Vector3 op2)
    {
        x = op1.y * op2.z - op1.z * op2.y;
        y = op1.z * op2.x - op1.x * op2.z;
        z = op1.x * op2.y - op1.y * op2.x;
    }
	
	
    /**
     * Returns the dot product of this Vector3 object and the parameter Vector3.
     * 
     * @param rhs The right hand operand.
     * @return The dot product of this Vector3 object and the parameter Vector3.
     */
    double dot (Vector3 rhs)
    {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }
	
	
    /**
     * Returns the length of this vector.
     * 
     * @return The length of this vector.
     */
    double length ()
    {
        return Math.sqrt(lengthSquared());
    }
	
	
    /**
     * Returns the length squared of this vector. Very useful if only comparison
     * of lengths is needed since it saves the square root.
     * 
     * @return the length squared of this vector3
     */
    double lengthSquared ()
    {
        return x * x + y * y + z * z;
    }
	
	
    /**
     * This method will normalize this Vector3 so that its length is 1.0. If the
     * length of the Vector3 is 0, no action is taken.
     */
    void normalize ()
    {
        double dist = length();
        if (dist != 0)
        {
            x /= dist;
            y /= dist;
            z /= dist;
        }
    }
	
	
    /**
     * Add a Vector3 to this Vector3
     * 
     * @param vector the Vector3 to add
     */
    void add (Vector3 vector)
    {
        add(this, vector);
    }
	
	
    /**
     * Add the values of Vector3 v1 and Vector3 v2 and store the sum in this
     * Vector3.
     * 
     * @param v1 the first operand
     * @param v2 the second operand
     */
    void add (Vector3 v1, Vector3 v2)
    {
        x = v1.x + v2.x;
        y = v1.y + v2.y;
        z = v1.z + v2.z;
    }
	
	
    /**
     * Subtract a Vector3 from this Vector3
     * 
     * @param vector the Tuple3 to subtract
     */
    void sub (Vector3 vector)
    {
        x -= vector.x;
        y -= vector.y;
        z -= vector.z;
    }
	
	
    /**
     * Subtract one Point3 from another Point3 and set as this Vector
     * 
     * @param p1 the first operand
     * @param p2 the second operand
     */
    void sub (Point3 p1, Point3 p2)
    {
        x = p1.x - p2.x;
        y = p1.y - p2.y;
        z = p1.z - p2.z;
    }
	
	
    /**
     * Add a scalar multiple of a Vector3 to this Vector3
     * 
     * @param scale the scale factor
     * @param vector the vector to scale add
     */
    void scaleAdd (double scale, Tuple3 vector)
    {
        x += scale * vector.x;
        y += scale * vector.y;
        z += scale * vector.z;
    }
};

public class Color
{
public:
    /** The red component. */
    double r;
	
    /** The green component. */
    double g;
	
    /** The blue component. */
    double b;
	
	
    /**
     * Default constructor. Produces black.
     */
    Color ()
    {
        Color(0, 0, 0);
    }
	
	
    /**
     * Copy constructor.
     * 
     * @param newColor The color to copy.
     */
    Color (Color newColor)
    {
        Color(newColor.r, newColor.g, newColor.b);
    }
	
	
    /**
     * The explicit constructor.
     * 
     * @param newR The new red value.
     * @param newG The new green value.
     * @param newB The new blue value.
     */
    Color (double newR, double newG, double newB)
    {
        r = newR;
        g = newG;
        b = newB;
    }
	
	
    /**
     * Sets this color to the value of inColor.
     * 
     * @param inColor the input color
     */
    void set (Color inColor)
    {
        r = inColor.r;
        g = inColor.g;
        b = inColor.b;
    }
	
	
    /**
     * Sets the value of this color to (inR, inG, inB)
     * 
     * @param inR the input red value
     * @param inG the input green value
     * @param inB the input blue value
     */
    void set (double inR, double inG, double inB)
    {
        r = inR;
        g = inG;
        b = inB;
    }
	
	
    /**
     * Sets this color as the product of the pairwise product of this color and
     * rhs.
     * 
     * @param rhs The right hand argument.
     */
    void scale (Color rhs)
    {
        r *= rhs.r;
        g *= rhs.g;
        b *= rhs.b;
    }
	
	
    /**
     * Scales each compoenent of this color by rhs.
     * 
     * @param rhs The scale value to use.
     */
    void scale (double rhs)
    {
        r *= rhs;
        g *= rhs;
        b *= rhs;
    }
	
	
    /**
     * Sets this color to the pairwise sum of this color and ths.
     * 
     * @param rhs the input color
     */
    void add (Color rhs)
    {
        r += rhs.r;
        g += rhs.g;
        b += rhs.b;
    }
	
	
    /**
     * Adds rhs scaled by scale pairwise to this color.
     * 
     * @param scale the scale factor
     * @param rhs the color to be scaled and added
     */
    void scaleAdd (double scale, Color rhs)
    {
        r += scale * rhs.r;
        g += scale * rhs.g;
        b += scale * rhs.b;
    }
	
	
    /**
     * Clamps the each component of this color to between [min,max]
     * 
     * @param min the minimum value
     * @param max the maximum value
     */
    void clamp (double min, double max)
    {
        r = max(min(r, max), min);
        g = max(min(g, max), min);
        b = max(min(b, max), min);
    }
	
	
    /**
     * This function returns an int which represents this color. The standard
     * RGB style bit packing is used and is compatible with
     * java.awt.BufferedImage.TYPE_INT_RGB. (ie - the low 8 bits, 0-7 are for
     * the blue channel, the next 8 are for the green channel, and the next 8
     * are for the red channel). The highest 8 bits are left untouched.
     * 
     * @return An integer representing this color.
     */
    int toInt ()
    {
        int iR, iG, iB;
		
        // Here we do the dumb thing and simply clamp then scale.
        // The "+ 0.5" is to achieve a "round to nearest" effect
        // since Java float to int casting simply truncates.
        iR = (int)(255.0 * max(min(r, 1.0), 0.0) + 0.5);
        iG = (int)(255.0 * max(min(g, 1.0), 0.0) + 0.5);
        iB = (int)(255.0 * max(min(b, 1.0), 0.0) + 0.5);
		
        // Bit packing at its finest
        return (iR << 16) | (iG << 8) | (iB << 0);
    }
	
	
    /**
     * @see Object#toString()
     */
    string toString ()
    {
        return "[" + r + "," + g + "," + b + "]";
    }
};
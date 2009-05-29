/***************************************************************************
 * file:        CoordSpherical.h
 *
 * author:      Christian
 *
 *					 Inspired by NASA World Wind Java.
 ***************************************************************************
 * part of:     framework implementation developed by DLR/KN-FS
 **************************************************************************/


#ifndef _COORDSPHERICAL_H
#define _COORDSPHERICAL_H

#include <omnetpp.h>
#include "INETDefs.h"
#include "FWMath.h"
#include "CoordSpherical.h"

#ifndef M_PI
#define M_PI	3.141592653589793238462643383279502
#endif


#define	Angle	double
// earth radius in meters
#define	EARTH_RADIUS			6378137
// constants for calculations between degrees and radians
#define	DEGREES_TO_RADIANS	(Angle)(M_PI / 180)
#define	RADIANS_TO_DEGREES	(Angle)(180 / M_PI)
#define	PIOver2					(Angle)(M_PI / 2)
// degree constants
#define	ZERO						   0
#define	POS90						  90
#define	NEG90						 -90
#define	POS180					 180
#define	NEG180					-180
#define	POS360					 360


/**
 * @brief Class for storing host positions
 *
 * Class for a triple storing (latitude, longitude, elevation).
 * Some comparison and basic arithmetic operators on CoordSpherical
 * structures are implemented.
 *
 * @ingroup support
 * @author Christian
 */
class INET_API CoordSpherical : public cPolymorphic
{
public:
  /** @brief latitude, longitude and elevation of the position */
  Angle latitude;
  Angle longitude;
  double elevation;

public:
	CoordSpherical()
	{
		latitude;
		longitude;
		elevation = 0;
	}

	/** Initializes coordinates.*/
	CoordSpherical(Angle _latitude, Angle _longitude, float _elevation) : latitude(_latitude), longitude(_longitude), elevation(_elevation) {};

	/** Copy constructor: initializes coordinates.*/
	CoordSpherical(const CoordSpherical& pos)
	{
		latitude = pos.latitude;
		longitude = pos.longitude;
		elevation = pos.elevation;
	}

	std::string info() const
	{
		std::stringstream os;
		os << "(" << latitude << "," << longitude << "," << elevation << " )";
		return os.str();
	}

	static CoordSpherical getZeroCoord()
	{
		return CoordSpherical(ZERO, ZERO, 0);
	}

	static CoordSpherical fromRadians(Angle latitude, Angle longitude, float elevation)
	{
		return CoordSpherical(RADIANS_TO_DEGREES * latitude, RADIANS_TO_DEGREES * longitude, elevation);
	}

	static CoordSpherical fromDegrees(Angle latitude, Angle longitude, float elevation)
	{
		return CoordSpherical(latitude, longitude, elevation);
	}

/*
	---------
	Operators
	---------
*/

	/** Adds two coordinate vectors.*/
	friend CoordSpherical operator+(CoordSpherical a, CoordSpherical b)
	{	
		  return CoordSpherical(a.latitude+b.latitude, a.longitude+b.longitude, a.elevation+b.elevation);
	}

	/** Subtracts two coordinate vectors.*/
	friend CoordSpherical operator-(CoordSpherical a, CoordSpherical b)
	{
		  return CoordSpherical(a.latitude-b.latitude, a.longitude-b.longitude, a.elevation-b.elevation);
	}

	/** Adds coordinate vector b to a.*/
	CoordSpherical operator+=(CoordSpherical a)
	{
		  latitude+=a.latitude;
		  longitude+=a.longitude;
		  elevation+=a.elevation;
		  return *this;
	}

	/** subtracts coordinate vector b from a.*/
	CoordSpherical operator-=(CoordSpherical a)
	{
		  latitude-=a.latitude;
		  longitude-=a.longitude;
		  elevation-=a.elevation;
		  return *this;
	}

	/** Subtracts two coordinate vectors.*/
//	friend Coord operator-(Coord a, Coord b) {
//        return Coord(a.x-b.x, a.y-b.y);
//  }

  /** Multiplies a coordinate vector by a real number.*/
	friend CoordSpherical operator*(CoordSpherical a, double f) {
		return CoordSpherical(a.latitude*f, a.longitude*f, a.elevation*f);
	}
  /** Divides a coordinate vector by a real number.*/
	friend CoordSpherical operator/(CoordSpherical a, double f) {
		return CoordSpherical(a.latitude/f, a.longitude/f, a.elevation/f);
	}

  /** Adds coordinate vector b to a.*/
//	Coord operator+=(Coord a) {
//    x+=a.x;
//    y+=a.y;
//    return *this;
//  }

  /** Subtracts coordinate vector b from a.*/
/*
	Coord operator-=(Coord a) {
    x-=a.x;
    y-=a.y;
    return *this;
  }
*/

	/** Copy rhs to this. */
	CoordSpherical operator=(const CoordSpherical& rhs)
	{
		if (this != &rhs)
		{
			latitude = rhs.latitude;
			longitude = rhs.longitude;
			elevation = rhs.elevation;
		}
		return *this;
	}

	/**
   * Tests whether two coordinate vectors are equal. Because
   * coordinates are of type floating point, this is done through
	* the FWMath::close function.
   */
	friend bool operator==(CoordSpherical& lhs, CoordSpherical& rhs)
	{
		// TODO elevation could probably be more coarse grained?
		return FWMath::close(lhs.latitude, rhs.latitude) && FWMath::close(lhs.longitude, rhs.longitude) && FWMath::close(lhs.elevation, rhs.elevation);
		//return false;
	}

  /**
   * Tests whether two coordinate vectors are not equal. Negation of
   * the operator==.
   */
	friend bool operator!=(CoordSpherical& lhs, CoordSpherical& rhs)
	{
		return !(lhs==rhs);
	}

	/**
	* Returns distance^2 to CoordSpherical a
	*/
/*	float sqrdist(const CoordSpherical& a) const
	{
		// distance based on great circle
		// Haversine formula
		// ref.: http://www.movable-type.co.uk/scripts/latlong.html
		double d_lat = DEGREES_TO_RADIANS * (a.latitude - this->latitude);
		double d_long = DEGREES_TO_RADIANS * (a.longitude - this->longitude);

		double b = ::sin(d_lat/2) * ::sin(d_lat/2) + ::cos(DEGREES_TO_RADIANS * this->latitude) * ::cos(DEGREES_TO_RADIANS * a.latitude) * sin(d_long/2) * sin(d_long/2);
		double c = EARTH_RADIUS * 2.0 * ::atan2(::sqrt(b),::sqrt(1.0-b));

		// now we use pythagoras to include the elevation into the distance
		return (Angle) (c * c + (this->elevation - a.elevation) * (this->elevation - a.elevation));
	}*/

	float sqrdist(const CoordSpherical& a) const
	{
		double r = EARTH_RADIUS + this->elevation;
		double theta = (90 - this->latitude) * DEGREES_TO_RADIANS;
		double phi = fmod( (this->longitude + 360) , 360 ) * DEGREES_TO_RADIANS;

		double r2 = EARTH_RADIUS + a.elevation;
		double theta2 = (90 - a.latitude) * DEGREES_TO_RADIANS;
		double phi2 = fmod( (a.longitude + 360) , 360 ) * DEGREES_TO_RADIANS;

		return (r*r + r2*r2 - 2*r*r2*( cos(theta)*cos(theta2) + sin(theta)*sin(theta2)*cos(phi-phi2) ));
	}



  /**
   * Returns the distance to CoordSpherical a
   */
	float distance(const CoordSpherical& a) const
	{
		return (Angle) ::sqrt( sqrdist(a) );
	}

	/**
	* Returns the distance to CoordSpherical a in radians
	* Based on algorithm at http://williams.best.vwh.net/avform.htm#Crs
	* Note that differences in elevation are not considered!
	*/
	float distanceRad(const CoordSpherical& a)
	{
		double theta = (this->latitude) * DEGREES_TO_RADIANS;
		double phi = - this->longitude * DEGREES_TO_RADIANS;
	
		double theta2 = (a.latitude) * DEGREES_TO_RADIANS;
		double phi2 = - a.longitude * DEGREES_TO_RADIANS;

		double A = pow(sin((theta-theta2)/2),2);
		double B = pow(sin((phi-phi2)/2),2);	
	
		return (2 * asin(sqrt(A+cos(theta)*cos(theta2)*B)));	
	}

	/**
	 * Parses the content of the passed radian coordinate and writes the converted
	 * decimal lat/lon values to the respective passed arguments.
	 */
	static void convertCoordinate(std::string& coordinate, std::string& coord_lat, std::string& coord_lon)
	{
		if (coordinate.length() != 11)
			opp_error("Coordinate invalid - must have length 11!");

		float latitude, longitude;
		char c_lat[15], c_lon[15];

		// Decimal degree DD = dd + mm/60.0 + ss/3600.
		//
		// FIXME
		// make conversion faster by using c like strings: start from back and set '\0's appropriately.
		latitude = (float) ( atof( coordinate.substr(0, 2).c_str() ) + atof( coordinate.substr(2, 2).c_str() ) / 60 );
		longitude = (float) ( atof( coordinate.substr(5, 3).c_str() ) + atof( coordinate.substr(8, 2).c_str() ) / 60 );

		if (coordinate[4] != 'N')
			latitude *= -1.0;

		if (coordinate[10] != 'E')
			longitude *= -1.0;

		// convert numbers to strings
		sprintf(c_lat, "%f", latitude);
		sprintf(c_lon, "%f", longitude);

		coord_lat = c_lat;
		coord_lon = c_lon;
	}

	/**
	 * Parses the content of the passed radian coordinate and writes the converted
	 * decimal lat/lon values back to the passed arguments.
	 */
	static void convertCoordinate13And14Digit(std::string& coord_lat, std::string& coord_lon)
	{
		if ( (coord_lat.length() != 13) && (coord_lon.length() != 14) )
			opp_error("Coordinate invalid - must have length 13 or 14!");

		float latitude, longitude;
		char c_lat[15], c_lon[15];

		// Decimal degree DD = dd + mm/60.0 + ss/3600.
		//
		// FIXME
		// make conversion faster by using c like strings: start from back and set '\0's appropriately.
		latitude = (float) ( atof( coord_lat.substr(2, 2).c_str() ) + atof( coord_lat.substr(5, 2).c_str() ) / 60 + atof( coord_lat.substr(8, 4).c_str() ) / 3600 );
		longitude = (float) ( atof( coord_lon.substr(2, 3).c_str() ) + atof( coord_lon.substr(6, 2).c_str() ) / 60 + atof( coord_lon.substr(9, 4).c_str() ) / 3600 );

		if (coord_lat[0] != 'N')
			latitude *= -1.0;

		if (coord_lon[0] != 'E')
			longitude *= -1.0;

		// convert numbers to strings
		sprintf(c_lat, "%f", latitude);
		sprintf(c_lon, "%f", longitude);

		coord_lat = c_lat;
		coord_lon = c_lon;
	}


	friend inline std::ostream& operator<<(std::ostream& os, const CoordSpherical& coord)
	{
		return os << "(" << coord.latitude << "," << coord.longitude << "," << coord.elevation << ")";
	}

	/**
	* calculates a sequence of nrPoints equally spaced waypoints along the Great Circle route to destination
	* implementation of algorithm found at http://williams.best.vwh.net/avform.htm#Crs
	* differences in elevation between the endpoints are interpolated linearly, i.e. the calculated route is a Great Circle along the surface of the Earth!
	*/
	std::vector<CoordSpherical> CoordSpherical::calculateGreatCircleRoute(const CoordSpherical& destination, int nrPoints)
	{	
		float step = 1.0 / nrPoints; 
		float f = 0; // fraction of distance between start and end point
	
		float currentLat, currentLon;
		CoordSpherical currentWaypoint;
		std::vector<CoordSpherical> waypoints;
		waypoints.push_back(*this);	
	
		// calculate distance between endpoints in radians
		float d = distanceRad(destination);
	
		// pre-calculate some values to save time
		float sin_d = sin(d);
		float sin_lat_rad = sin(DEGREES_TO_RADIANS * latitude);
		float cos_lat_rad = cos(DEGREES_TO_RADIANS * latitude);
		float sin_lon_rad = sin(-DEGREES_TO_RADIANS * longitude);
		float cos_lon_rad = cos(-DEGREES_TO_RADIANS * longitude);
		float sin_dest_lon_rad = sin(-DEGREES_TO_RADIANS * destination.longitude); // algorithm assumes that Western longitudes are positive
		float cos_dest_lon_rad = cos(-DEGREES_TO_RADIANS * destination.longitude);
		float sin_dest_lat_rad = sin(DEGREES_TO_RADIANS * destination.latitude);
		float cos_dest_lat_rad = cos(DEGREES_TO_RADIANS * destination.latitude);
		float deltaElev = destination.elevation - elevation;
	
		for (int i=0; i<nrPoints-1; i++)	
		{
			f = f + step;	
		
			float A = sin((1-f)*d)/sin_d;
			float B = sin(f*d)/sin_d;		

			float x = A*cos_lat_rad*cos_lon_rad +  B*cos_dest_lat_rad*cos_dest_lon_rad;
			float y = A*cos_lat_rad*sin_lon_rad +  B*cos_dest_lat_rad*sin_dest_lon_rad;
			float z = A*sin_lat_rad		       	 +  B*sin_dest_lat_rad;

			currentLat = atan2(z,sqrt(pow(x,2)+pow(y,2)));
			currentLon = atan2(y,x);
		
			// convert back to degrees
			currentLat = RADIANS_TO_DEGREES * currentLat;
			currentLon = -RADIANS_TO_DEGREES * currentLon;
		
			currentWaypoint.latitude = currentLat;
			currentWaypoint.longitude = currentLon;
			currentWaypoint.elevation = elevation + f*deltaElev;
			waypoints.push_back(currentWaypoint);
		}
	
		waypoints.push_back(destination);
	
		return waypoints;	
	}

};

#endif

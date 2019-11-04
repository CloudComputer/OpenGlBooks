//-------------------------------------------------------------------------------
// PlayerViz (Player Trace Visualizer) 
// Version 0.5 Released 08.10.2007
// Part of the CGUL (Common Games Understanding and Learning) Toolkit
//-------------------------------------------------------------------------------
//  Copyright (C) 2007 Priyesh N. Dixit and G. Michael Youngblood
//  Game Intelligence Group, Games + Learning Lab
//  The University of North Carolina at Charlotte
//  College of Computing and Informatics, Department of Computer Science
//  9201 University City Blvd, Charlotte, NC 28223-0001
//  {pndixit, youngbld}@uncc.edu
//-------------------------------------------------------------------------------
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
//-------------------------------------------------------------------------------

#ifndef CGUL_DATA_H
#define CGUL_DATA_H

#include <vector>
#include <string>

#include "SSPSGeometry.h"

struct PlayerMove {
	float x,y,z;
	float h,p,r;
	float speed;
	float etime;
	float health;
	float shots;
	float time_score;
	float capture;
    ViewFrustum viewPoint;
};

class CGULData 
{
public:
	std::string dataDirectory;
	std::string currentMap;
	std::string imagePath;
	float worldScale;
	
	//SSPS file info
	SSPSGeometry ssps;

	//player trace data file info
	std::vector< std::vector<PlayerMove> > playerTraces;
	std::vector<bool> capturedFlag;

	//DIAS file info
	SSPSVertex flagPosition;
	int flagPositionID;
	
	
	CGULData();
	
	void readPlayerTraceFile(const char* filename);
    void readSSPSFile(const char* sspspath);
	void readDiasData(std::string filename);

	void clearData();
	bool removeTrace(int i);
	void setDataDirectory(std::string dir);
};

#endif

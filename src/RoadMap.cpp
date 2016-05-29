/*
 * Map.cpp
 *
 *  Created on: 16/04/2016
 *      Author: Ines
 */

#include <values.h>
#include <float.h>
#include "RoadMap.h"

bool RoadMap::instanceFlag = false;
RoadMap* RoadMap::rm = NULL;
RoadMap* RoadMap::getInstance()
{
	if(! instanceFlag)
	{
		rm = new RoadMap("Nodes.csv", "Roads.csv", "SubRoads.csv");
		instanceFlag = true;
		return rm;
	}
	else
	{
		return rm;
	}
}

void RoadMap::readNodesFile(const std::string& fnodes){
	std::ifstream nodes;
	string str;
	stringstream ss;

	nodes.open(fnodes.c_str());
	if(!nodes.is_open()){
		std::cout << "Nodes file does not exist\n";
		return;
	}

	while(!nodes.eof()){
		uint id;
		float lat_d, lat_r;
		float lon_d, lon_r;
		char lixo;

		ss.clear();
		getline(nodes, str, '\n');
		ss << str;
		ss >> id >> lixo >> lat_d >> lixo >> lon_d >> lixo >> lon_r >> lixo >> lat_r;

		if(lat_d < latitude_min)
			latitude_min = lat_d;
		if(lat_d > latitude_max)
			latitude_max = lat_d;

		if(lon_d < longitude_min)
			longitude_min = lon_d;
		if(lon_d > longitude_max)
			longitude_max = lon_d;

		Crossroad c(id, lat_d, lon_d, lon_r, lat_r);

		crossRoads.insert(std::pair<uint,Crossroad>(id, c));

		this->addVertex(c);

	}
	nodes.close();
}

void RoadMap::readRoadsFile(const std::string& froads){
	std::ifstream roads;
	string str;
	stringstream ss;

	roads.open(froads.c_str());

	while(!roads.eof()){
		uint id;
		string name;
		bool isTwoWay;

		getline(roads, str, ';');
		ss.clear();
		ss << str;
		ss >> id;

		getline(roads, name, ';');
		getline(roads, str, '\n');

		if(str == "True")
			isTwoWay = true;
		else
			isTwoWay = false;

		Road r(name, isTwoWay);
		this->roads.insert(std::pair<uint,Road>(id, r));
	}
	roads.close();
}

void RoadMap::readSubRoadsFile(const std::string& fsubroads){
	std::ifstream subroads;
	int i = 0;

	subroads.open(fsubroads.c_str());
	if(!subroads.is_open()){
		std::cout << "subroads file does not exist\n";
		return;
	}
	while(!subroads.eof()){
		string str;
		stringstream ss;
		uint id_road, id_node1, id_node2;
		char lixo;

		ss.clear();
		getline(subroads, str, '\n');
		ss << str;
		ss >> id_road >> lixo >> id_node1 >> lixo >> id_node2;

		//TODO Falta conferir se os id est�o em crossroads/roads.
		Crossroad* c1 = &crossRoads.find(id_node1)->second;
		Crossroad* c2 = &crossRoads.find(id_node2)->second;
		Road* r = &roads.find(id_road)->second;
		r->addCrossroad(c1);
		r->addCrossroad(c2);

		uint dist = c1->getDist(*c2);

		if(!this->addEdge(*c1, *c2, dist, r))
			cerr << "Edge ups..." << id_node1 << " " << id_node2 << endl;

		if(r->isTwoWay()){
			if(!this->addEdge(*c2, *c1, dist, r))
				cerr << "Edge ups..." << id_node2 << " " << id_node1 << endl;
			i++;
		}
		i++;
	}
	subroads.close();

	cout << i;
}

RoadMap::RoadMap(const std::string& fnodes, const std::string& froads, const std::string& fsubroads){

	latitude_min = 180;
	longitude_min = 180;
	longitude_max = -180;
	latitude_max = -180;

	readNodesFile(fnodes);
	cout << this->crossRoads.size() << " nodes loaded" << endl;
	readRoadsFile(froads);
	cout << this->roads.size() << " roads loaded" << endl;
	readSubRoadsFile(fsubroads);
	cout << " edges loaded" << endl;

	//floydWarshallShortestPath();

	cout << "latitude_min: " << latitude_min << endl;
	cout << "latitude_max: " << latitude_max << endl;
	cout << "longitude_min: " << longitude_min << endl;
	cout << "longitude_max: " << longitude_max << endl;

}

void RoadMap::resetMap(){
	vector<Vertex<Crossroad, Road> *>::iterator it = vertexSet.begin();
	vector<Vertex<Crossroad, Road> *>::iterator ite = vertexSet.end();

	while(it != ite){
		gv->setVertexSize((*it)->getInfo().getId(), 5);
		gv->setVertexColor((*it)->getInfo().getId(),"blue");
		it++;
	}
}

void RoadMap::viewMap(){
	uint width = 1360;
	uint height = 1300;

	gv = new GraphViewer(width, height, false);

	//Colocar a imagem �background.jpg� como fundo
	gv->setBackground("background.jpg");

	gv->createWindow(width/2, height/2);

	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
	gv->defineEdgeCurved(false);

	{
		vector<Vertex<Crossroad, Road> *>::iterator it = vertexSet.begin();
		vector<Vertex<Crossroad, Road> *>::iterator ite = vertexSet.end();

		while(it != ite){
			gv->addNode((*it)->getInfo().getId(),width*((*it)->getInfo().getLongitudeInDegrees()-longitude_min)/(longitude_max-longitude_min) ,height - (height*((*it)->getInfo().getLatitudeInDegrees()-latitude_min)/(latitude_max-latitude_min)));
			gv->setVertexSize((*it)->getInfo().getId(), 5);
			//gv->setVertexLabel((*it)->getInfo().getId(), ".");
			it++;
		}
	}

	{
		vector<Vertex<Crossroad, Road> *>::iterator it = vertexSet.begin();
		vector<Vertex<Crossroad, Road> *>::iterator ite = vertexSet.end();
		int id = 0;

		while(it != ite){
			vector<Edge<Crossroad, Road> > edge = (*it)->getAdj();
			for (unsigned int i = 0; i < (*it)->getAdj().size(); ++i) {
				gv->addEdge(id, (*it)->getInfo().getId(), edge[i].getDest()->getInfo().getId(), EdgeType::DIRECTED);
				id++;
			}
			it++;
		}
	}

	gv->rearrange();
}

void RoadMap::insertNewSrc(uint srcId, uint destId, uint newSrc, list<uint>&mustPass, list<uint> &path, list<double> &dist){

	Crossroad src = crossRoads.find(srcId)->second;
	list<uint>::iterator next;

	dijkstraShortestPath(src);

	double minDist = DBL_MAX;

	for (list<uint>::iterator it = mustPass.begin(); it != mustPass.end(); ++it) {
		Crossroad tmp = crossRoads.find(*it)->second;
		if(getVertex(tmp)->getDist() < minDist){
			minDist = getVertex(tmp)->getDist();
			next = it;
		}
	}

	if(minDist == INT_INFINITY){
		return;
	}
	if(*next == newSrc){
		dist.push_back(dist.back() + minDist);
		path.push_back(*next);

		mustPass.erase(next);

	}
	else{
		dist.push_back(dist.back() + minDist);
		path.push_back(*next);

		mustPass.erase(next);


		insertNewSrc(path.back(), destId, newSrc, mustPass, path, dist);
	}

}

bool RoadMap::insertNewDest(uint srcId, uint destId, list<uint> mustPass, list<uint> &path, list<double> &dist){
	Crossroad src = crossRoads.find(srcId)->second;
	list<uint>::iterator next;

	dijkstraShortestPath(src);

	if(mustPass.empty()){
		Crossroad dest = crossRoads.find(destId)->second;
		double minDist = getVertex(dest)->getDist();

		dist.push_back(dist.back() + minDist);
		path.push_back(destId);
	}
	else{
		double minDist = DBL_MAX;

		for (list<uint>::iterator it = mustPass.begin(); it != mustPass.end(); ++it) {
			Crossroad tmp = crossRoads.find(*it)->second;
			if(getVertex(tmp)->getDist() < minDist){
				minDist = getVertex(tmp)->getDist();
				next = it;
			}
		}

		dist.push_back(dist.back() + minDist);
		path.push_back(*next);

		mustPass.erase(next);

		insertNewDest(path.back(), destId, mustPass, path, dist);
	}

	return true;
}

void RoadMap::bestPath(uint newSrc, uint newDest, list<uint> &oldPath, list<double> &dist){
	list<uint> newPath;
	list<uint> mustPass = oldPath;
	uint src = oldPath.front();
	uint dest = oldPath.back();

	mustPass.pop_front();
	mustPass.pop_back();

	//Test if newSrc is already a point of interest
	bool newSrcIsInPath = false;

	{
		list<uint>::const_iterator it = mustPass.begin();
		list<uint>::const_iterator ite = mustPass.end();

		while(it != ite){
			if(*it == newSrc)
				newSrcIsInPath = true;

			it++;
		}

	}
	newPath.push_back(src);
	dist.clear();
	dist.push_back(0);


	if(newSrc != src) {
		if (!newSrcIsInPath)
			mustPass.push_back(newSrc);

		//Insert newSrc in path

		insertNewSrc(src, dest, newSrc, mustPass, newPath, dist);
	}
	//Check if adding newDest is needed
	bool newDestIsInPath = false;

	{
		list<uint>::const_iterator it = mustPass.begin();
		list<uint>::const_iterator ite = mustPass.end();

		while(it != ite){
			if(*it == newDest)
				newDestIsInPath = true;

			it++;
		}

	}

	if(!newDestIsInPath && newDest != dest)
		mustPass.push_back(newDest);

	//Complete path inserting
	insertNewDest(newSrc, dest, mustPass, newPath, dist);

	oldPath.clear();

	oldPath.insert(oldPath.end(),newPath.begin(),newPath.end());
}

uint RoadMap::getCrossroadIdFromAddress(string roadName, double doorNumber){
	uint id = -1;

	for (map<uint, Road>::iterator it = roads.begin(); it != roads.end() && id == -1; it++) {
		id = it->second.getNodeId(roadName, doorNumber);
	}

	return id;
}

bool RoadMap::validCrossroadId(uint id){
	Crossroad c = crossRoads.find(id)->second;

	return id == c.getId();
}

double RoadMap::getDist(uint srcId, uint destId){
	Crossroad src = crossRoads.find(srcId)->second;
	Crossroad dest = crossRoads.find(destId)->second;

	dijkstraShortestPath(src);

	return getVertex(dest)->getDist();
}

vector<string> RoadMap::getRoadsPassed(list<uint> path){

	vector<string> roadsPassed;

	list<uint>::const_iterator it = path.begin();
	list<uint>::const_iterator ite = path.end();

	Crossroad src = crossRoads.find(*it)->second;
	it++;

	while(it != ite){
		dijkstraShortestPath(src);

		Crossroad dest = crossRoads.find(*it)->second;
		vector<Road*> subPath = getEdgePath(src, dest);

		for (int i = 0; i < subPath.size(); ++i) {
			if(!roadsPassed.empty()){
				if(roadsPassed.back() != subPath[i]->getName())
					roadsPassed.push_back(subPath[i]->getName());
			}
			else
				roadsPassed.push_back(subPath[i]->getName());
		}

		src = dest;
		it++;
	}

	return roadsPassed;
}

void RoadMap::visualizePath(list<uint> path){

	this->resetMap();
	uint stopNo = 1;
	list<uint>::const_iterator it = path.begin();
	list<uint>::const_iterator ite = path.end();

	Crossroad c = crossRoads.find(*it)->second;
	dijkstraShortestPath(c);

	//Set path source orange
	gv->setVertexColor(*it, "orange");
	gv->setVertexSize(*it, 20);

	it++;

	while(it != ite){
		//Sleep(1000);

		dijkstraShortestPath(c);

		Crossroad tmp = crossRoads.find(*it)->second;
		vector<Crossroad> subPath = getPath(c, tmp);
		stringstream ss;

		ss << "Paragem " << stopNo;

		for (uint i = 1; i < subPath.size()-1; ++i) {
			gv->setVertexColor(subPath[i].getId(), "yellow");
			gv->setVertexSize(subPath[i].getId(), 10);
		}

		gv->setVertexColor(*it, "pink");
		gv->setVertexSize(*it, 20);
		gv->setVertexLabel(*it, ss.str());

		gv->rearrange();
		c=tmp;

		stopNo++;
		it++;
	}

	//Set path destination red
	it--;
	gv->setVertexColor(*it, "red");
	gv->setVertexLabel(*it, "Destino");

	gv->rearrange();
}

RoadMap::~RoadMap(){}



/*=========================================================================

 Program:   Visualization Toolkit

 Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
 All rights reserved.
 See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

   This software is distributed WITHOUT ANY WARRANTY; without even
   the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
   PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkMapTile -
// .SECTION Description
//

#ifndef __vtkMapTile_h
#define __vtkMapTile_h

#include "vtkFeature.h"
#include "vtkmap_export.h"

class vtkStdString;
class vtkPlaneSource;
class vtkActor;
class vtkPolyDataMapper;
class vtkTextureMapToPlane;

class VTKMAP_EXPORT vtkMapTile : public vtkFeature
{
public:
  static vtkMapTile* New();
  virtual void PrintSelf(ostream &os, vtkIndent indent);
  vtkTypeMacro (vtkMapTile, vtkFeature)

  // Description:
  // Get/Set Bing Maps QuadKey corresponding to the tile
  void SetImageKey(const std::string& key)
    {
    this->ImageKey = key;
    }

  void  SetImageSource(const std::string& imgSrc) {this->ImageSource= imgSrc;}
  std::string GetImageSource() {return this->ImageSource;}

  // Description:
  // Get/Set corners of the tile (lowerleft, upper right)
  vtkGetVector4Macro(Corners, double);
  vtkSetVector4Macro(Corners, double);

  // Description:
  // Get/Set bin of the tile
  vtkGetMacro(Bin, int);
  vtkSetMacro(Bin, int);

  // Description:
  vtkGetMacro(Plane, vtkPlaneSource*)
  vtkGetMacro(Actor, vtkActor*)
  vtkGetMacro(Mapper, vtkPolyDataMapper*)

  // Description:
  // Get/Set position of the tile
  void SetCenter(double* center);
  void SetCenter(double x, double y, double z);

  void SetVisible(bool val);
  bool IsVisible();

  // Description:
  // Create the geometry and download
  // the image if necessary
  virtual void Init();

  // Description:
  // Remove drawables from the renderer and
  // perform any other clean up operations
  virtual void CleanUp();

  // Description:
  // Update the map tile
  virtual void Update();


protected:
  vtkMapTile();
  ~vtkMapTile();

  void Build(const char* cacheDirectory);

  // Description:
  // Check if the corresponding image is downloaded
  bool IsImageDownloaded(const char* outfile);

  // Description:
  // Download the image corresponding to the Bing Maps QuadKey
  void DownloadImage(const char* url, const char* outfilename);

  // Description:
  // Generate url of tile and output file from QuadKey, and download the texture
  // if not already downloaded.
  void InitializeDownload(const char *cacheDirectory);

  // Description:
  // Storing the Quadkey
  std::string ImageSource;
  std::string ImageFile;
  std::string ImageKey;

  vtkPlaneSource* Plane;
  vtkTextureMapToPlane* TexturePlane;
  vtkActor* Actor;
  vtkPolyDataMapper* Mapper;

  int Bin;
  bool VisibleFlag;
  double Corners[4];

private:
  vtkMapTile(const vtkMapTile&);  // Not implemented
  vtkMapTile& operator=(const vtkMapTile&); // Not implemented
};

#endif // __vtkMapTile_h

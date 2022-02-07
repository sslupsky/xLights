#pragma once

/***************************************************************
 * This source files comes from the xLights project
 * https://www.xlights.org
 * https://github.com/smeighan/xLights
 * See the github commit history for a record of contributing
 * developers.
 * Copyright claimed based on commit dates recorded in Github
 * License: https://github.com/smeighan/xLights/blob/master/License.txt
 **************************************************************/

#include <string>
#include <vector>
#include <glm/glm.hpp>

class wxXmlDocument;
class wxXmlNode;

class PreviewCamera
{
public:
    friend class ViewpointMgr;

    void Reset();

    PreviewCamera(bool is_3d_);
    virtual ~PreviewCamera();
    PreviewCamera(const PreviewCamera &cam);
    PreviewCamera& operator= (const PreviewCamera& rhs);
    glm::mat4& GetViewMatrix();

    float GetPosX() const { return posX; }
    float GetPosY() const { return posY; }
    float GetPosZ() const { return posZ; }
    float GetAngleX() const { return angleX; }
    float GetAngleY() const { return angleY; }
    float GetAngleZ() const { return angleZ; }
    float GetDistance() const { return distance; }
    float GetZoom() const { return zoom; }
    float GetPanX() const { return panx; }
    float GetPanY() const { return pany; }
    float GetPanZ() const { return panz; }
    float GetZoomCorrX() const { return zoom_corrx; }
    float GetZoomCorrY() const { return zoom_corry; }
    float GetIs3D() const { return is_3d; }
    const std::string& GetName() const { return name; }
    long GetMenuId() const { return menu_id; }
    long GetDeleteMenuId() const { return deletemenu_id; }

    void SetPosX(float value) { posX = value; mat_valid = false; }
    void SetPosY(float value) { posY = value; mat_valid = false; }
    void SetAngleX(float value);
    void SetAngleY(float value);
    void SetAngleZ(float value);
    void SetDistance(float value) { distance = value; mat_valid = false; }
    void SetZoom(float value) { zoom = value; mat_valid = false; }
    void SetPanX(float value) { panx = value; mat_valid = false; }
    void SetPanY(float value) { pany = value; mat_valid = false; }
    void SetPanZ(float value) { panz = value; mat_valid = false; }
    void SetZoomCorrX(float value) { zoom_corrx = value; mat_valid = false; }
    void SetZoomCorrY(float value) { zoom_corry = value; mat_valid = false; }
    void SetIs3D(bool value) { is_3d = value; mat_valid = false; }
    void SetName(std::string name_) { name = name_; mat_valid = false; }

protected:
    float posX;
    float posY;
    float posZ;
    float angleX;
    float angleY;
    float angleZ;
    float distance;
    float zoom;
    float panx;
    float pany;
    float panz;
    float zoom_corrx;
    float zoom_corry;
    bool is_3d;
    std::string name;
    const long menu_id;
    const long deletemenu_id;
    bool mat_valid;
    glm::mat4 view_matrix;
};

class ViewpointMgr
{
public:
    ViewpointMgr();
    virtual ~ViewpointMgr();

    void Save(wxXmlDocument* doc);
    void Load(wxXmlNode* vp_node);

    void SetDefaultCamera2D(PreviewCamera* current_camera) { 
        if (_defaultCamera2D != nullptr) delete _defaultCamera2D; 
        _defaultCamera2D = new PreviewCamera(*current_camera); 
    }
    void SetDefaultCamera3D(PreviewCamera* current_camera) { 
        if (_defaultCamera3D != nullptr) delete _defaultCamera3D;
        _defaultCamera3D = new PreviewCamera(*current_camera);
    }
    void AddCamera( std::string name, PreviewCamera* current_camera, bool is_3d );
    int GetNum2DCameras() const { return static_cast<int>(previewCameras2d.size()); }
    int GetNum3DCameras() const { return static_cast<int>(previewCameras3d.size()); }
    PreviewCamera* GetCamera2D(int i) { return previewCameras2d[i]; }
    PreviewCamera* GetDefaultCamera2D() { return _defaultCamera2D; }
    PreviewCamera* GetDefaultCamera3D() { return _defaultCamera3D; }
    void DeleteCamera2D(int i);
    PreviewCamera* GetCamera3D(int i) { return previewCameras3d[i]; }
    void DeleteCamera3D(int i);
    PreviewCamera* GetNamedCamera3D(const std::string& name);
    void Clear();
    bool IsNameUnique(const std::string& name, bool is_3d);

private:
    wxXmlNode* Save() const;
    PreviewCamera* CreateCameraFromNode(wxXmlNode* node);
    wxXmlNode* SaveCameraToXml(PreviewCamera* camera, const std::string& nodename, const std::string& nameOverride) const;

    std::vector<PreviewCamera*> previewCameras3d;
    std::vector<PreviewCamera*> previewCameras2d;
    PreviewCamera* _defaultCamera2D = nullptr;
    PreviewCamera* _defaultCamera3D = nullptr;
};

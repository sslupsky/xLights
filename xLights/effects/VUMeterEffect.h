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

#include "RenderableEffect.h"
#include "../RenderBuffer.h"
#include <string>
#include <list>

#define VUMETER_OFFSET_MIN -100
#define VUMETER_OFFSET_MAX 100

#define VUMETER_GAIN_MIN -100
#define VUMETER_GAIN_MAX 100

class VUMeterEffect : public RenderableEffect
{
public:
    VUMeterEffect(int id);
    virtual ~VUMeterEffect();
    virtual void Render(Effect *effect, SettingsMap &settings, RenderBuffer &buffer) override;
    virtual void SetDefaultParameters() override;
    virtual void SetPanelStatus(Model *cls) override;
    virtual void RenameTimingTrack(std::string oldname, std::string newname, Effect* effect) override;
    virtual std::list<std::string> CheckEffectSettings(const SettingsMap& settings, AudioManager* media, Model* model, Effect* eff, bool renderCache) override;
    virtual bool needToAdjustSettings(const std::string &version) override;
    virtual void adjustSettings(const std::string &version, Effect *effect, bool removeDefaults = true) override;
protected:
    virtual xlEffectPanel *CreatePanel(wxWindow *parent) override;
    static int DecodeType(const std::string&  type);
    static int DecodeShape(const std::string& shape);

    void Render(RenderBuffer &buffer, SequenceElements *elements,
        int bars, const std::string& type, const std::string& timingtrack, int sensitivity, const std::string& shape, bool slowdownfalls, int startnote, int endnote, int xoffset, int yoffset, int gain, bool logarithmicX);
    void RenderSpectrogramFrame(RenderBuffer &buffer, int bars, std::list<float>& lastvalues, std::list<float>& lastpeaks, std::list<int>& pauseuntilpeakfall, bool slowdownfalls, int startnote, int endnote, int xoffset, int yoffset, bool peak, int peakhold, bool line, bool logarithmicX, bool circle, int gain, int sensitivity, std::list<std::vector<wxPoint>>& lineHistory) const;
    void RenderVolumeBarsFrame(RenderBuffer &buffer, int bars, int gain);
    void RenderWaveformFrame(RenderBuffer &buffer, int bars, int yoffset, int gain, bool frameDetail);
    void RenderTimingEventFrame(RenderBuffer &buffer, int bars, int type, std::string timingtrack, std::list<int> &timingmarks);
    void RenderTimingEventTimedSweepFrame(RenderBuffer& buffer, int bars, int type, std::string timingtrack, int& nCount);
    void RenderOnFrame(RenderBuffer &buffer, int gain);
    void RenderOnColourFrame(RenderBuffer &buffer, int gain);
    void RenderPulseFrame(RenderBuffer &buffer, int fadeframes, std::string timingtrack, int& lasttimingmark);
    void RenderTimingEventColourFrame(RenderBuffer &buffer, int& colourindex, std::string timingtrack, int sensitivity);
    void RenderLevelColourFrame(RenderBuffer &buffer, int& colourindex, int sensitivity, int& lasttimingmark, int gain);
    void RenderIntensityWaveFrame(RenderBuffer &buffer, int bars, int gain);
    void RenderLevelPulseFrame(RenderBuffer &buffer, int fadeframes, int sensitivity, int& lasttimingmark, int gain);
    void RenderLevelJumpFrame(RenderBuffer& buffer, int fadeframes, int sensitivity, int& lasttimingmark, int gain, bool fullJump, float& lastVal);
    void RenderLevelBarFrame(RenderBuffer &buffer, int bars, int sensitivity, float& lastbar, int& colourindex, int gain, bool random);
    void RenderNoteLevelBarFrame(RenderBuffer &buffer, int bars, int sensitivity, float& lastbar, int& colourindex, int startNote, int endNote, int gain, bool random);
    void RenderLevelShapeFrame(RenderBuffer &buffer, const std::string& shape, float& lastsize, int scale, bool slowdownfalls, int xoffset, int yoffset, int usebars, int gain);
    void RenderTimingEventPulseFrame(RenderBuffer &buffer, int fadeframes, std::string timingtrack, float& lastsize);
    void RenderTimingEventPulseColourFrame(RenderBuffer &buffer, int fadeframes, std::string timingtrack, float& lastsize, int& colourindex);
    void RenderTimingEventBarFrame(RenderBuffer &buffer, int bars, std::string timingtrack, float& lastbar, int& colourindex, bool all, bool random);
    void RenderNoteOnFrame(RenderBuffer& buffer, int startNote, int endNote, int gain);
    void RenderNoteLevelPulseFrame(RenderBuffer& buffer, int fadeframes, int sensitivity, int& lasttimingmark, int startNote, int endNote, int gain);
    void RenderNoteLevelJumpFrame(RenderBuffer& buffer, int fadeframes, int sensitivity, int& lasttimingmark, int startNote, int endNote, int gain, bool fullJump, float& lastsize);
    void RenderTimingEventJumpFrame(RenderBuffer &buffer, int fallframes, std::string timingtrack, float& lastval, bool useAudioLevel, int gain);
    void RenderLevelPulseColourFrame(RenderBuffer &buffer, int fadeframes, int sensitivity, int& lasttimingmark, int& colourindex, int gain);
    void RenderDominantFrequencyColour(RenderBuffer& buffer, int sensitivity, int startNote, int endNote, bool gradient);

    void DrawBox(RenderBuffer& buffer, int startx, int endx, int starty, int endy, xlColor& color1);
    void DrawCircle(RenderBuffer& buffer, int x, int y, float radius, xlColor& color1);
    void DrawStar(RenderBuffer& buffer, int x, int y, float radius, xlColor& color1, int points);
    void DrawDiamond(RenderBuffer& buffer, int centerx, int centery, int size, xlColor& color1);
    void DrawSnowflake(RenderBuffer &buffer, int xc, int yc, double radius, int sides, xlColor color, double rotation = 0);
    void DrawHeart(RenderBuffer &buffer, int xc, int yc, double radius, xlColor color, int thickness = 1);
    void DrawTree(RenderBuffer &buffer, int xc, int yc, double radius, xlColor color, int thickness = 1);
    void DrawCandycane(RenderBuffer &buffer, int xc, int yc, double radius, xlColor color, int thickness = 1) const;
    void DrawCrucifix(RenderBuffer &buffer, int xc, int yc, double radius, xlColor color, int thickness = 1);
    void DrawPresent(RenderBuffer &buffer, int xc, int yc, double radius, xlColor color, int thickness = 1);

    inline float ApplyGain(float value, int gain) const;
};

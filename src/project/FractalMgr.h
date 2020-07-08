#pragma once

#include <string>
#include <map>
#include <mutex>

#include <SFGUI/Adjustment.hpp>

#include "Mandelbrot.h"
#include "Julia.h"

class FractalMgr
{
public:
    enum JuliaState
    {
        Animate,
        FollowCursor,
        None,
        Count
    };

public:
    FractalMgr();
    ~FractalMgr();

    void Update(sfg::Adjustment::Ptr cr, sfg::Adjustment::Ptr ci);
    void Draw();

    const std::map<std::string, FractalSet *> &GetFractalSets() const noexcept { return m_fractalSets; }

    void SetFractalSet(const std::string &fractal);
    void SetIterationCount(size_t iterations);
    void SetJuliaC(const std::complex<double> c);
    void SetDrawComplexLines(bool onoff) noexcept { m_drawComplexLines = onoff; }

    void SetJuliaSetState(JuliaState state) noexcept { m_juliaState = state; }

private:
    // Used to only make the GUI send updates ONCE every frame so that the adjustment bars doesn't freeze the screen
    bool m_updatedThisFrame;

    std::map<std::string, FractalSet *> m_fractalSets;
    std::string m_activeFractalSet;

    std::pair<sf::Vector2f, sf::Vector2f> m_lastViewport;

    bool m_drawComplexLines;

    JuliaState m_juliaState;
    float m_animationTimer;

    // Cached
    size_t m_iterations;
};
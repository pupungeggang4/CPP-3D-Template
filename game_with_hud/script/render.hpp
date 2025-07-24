#pragma once
#include "general.hpp"

template <class TG, class TC>
void renderCuboid(TG *game, TC *cuboid) {
    glUniform1i(game->luModeV, 1);
    glUniform1i(game->luModeF, 1);
    glUniform3f(game->luColor, 0.0, 1.0, 0.0);
    glUniform3f(game->luMSize, cuboid->size.x, cuboid->size.y, cuboid->size.z);
    glUniform3f(game->luMPos, cuboid->pos.x, cuboid->pos.y, cuboid->pos.z);
    glUniform3f(game->luMRot, cuboid->rot.x, cuboid->rot.y, cuboid->rot.z);
    glUniform4f(game->luCProj, 1.1, 4.0 / 3.0, 0.1, 10.0);
    glUniform3f(game->luCPos, 0.0, 0.0, 0.0);
    glUniform3f(game->luCRot, 0.0, 0.0, 0.0);
    glUniform3f(game->luLightD, 0.0, 0.0, 1.0);

    glBindBuffer(GL_ARRAY_BUFFER, game->bCuboid);
    glVertexAttribPointer(game->laPosition, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));
    glVertexAttribPointer(game->laTexcoord, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(game->laNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, game->bCuboidIndex);

    glEnableVertexAttribArray(game->laPosition);
    glEnableVertexAttribArray(game->laTexcoord);
    glEnableVertexAttribArray(game->laNormal);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, (void*)(0));
}
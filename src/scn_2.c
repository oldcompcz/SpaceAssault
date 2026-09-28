#include <stdlib.h>

#include "shooter.h"
#include "objpool.h"
#include "data.h"
#include "scenario.h"

// ---------------------------------------------------------------------------
// "Operation Honeycomb" - a routine patrol stumbles upon a hive-like planet
// nobody dares to go near; told in chapters, the deeper into the hive the
// more Grchkrx, each new kind introduced alone first in a simple wave (the
// player figures out its behaviour by watching, texts give only the slightest
// hints) and only then mixed with the others
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// texts
// ---------------------------------------------------------------------------

static const sDisplayText text_honey_title[] = {
    { { 24, 10 }, 0x0c, "SPACE ASSAULT" },
    { { 26, 13 }, 0x07, "episode II" },
    { { 21, 16 }, 0x0e, "OPERATION HONEYCOMB" },
};

static const sDisplayText text_honey_brief[] = {
    { { 15, 10 }, 0x07, "Routine patrol of the outer rim." },
    { { 16, 13 }, 0x07, "Nothing ever happens out here." },
    { { 26, 16 }, 0x07, "...right?" },
    { { 24, 21 }, 0x0f, "Ready, pilot?" },
};

static const sDisplayText text_honey_chapters[] = {
    { { 26, 12 }, 0x0e, "CHAPTER 1" },
    { { 24, 14 }, 0x0f, "ROUTINE PATROL" },
    { { 26, 12 }, 0x0e, "CHAPTER 2" },
    { { 26, 14 }, 0x0f, "THE QUIET" },
    { { 26, 12 }, 0x0e, "CHAPTER 3" },
    { { 25, 14 }, 0x0f, "THE NURSERY" },
    { { 26, 12 }, 0x0e, "CHAPTER 4" },
    { { 22, 14 }, 0x0f, "KNEE-DEEP IN HONEY" },
    { { 26, 12 }, 0x0e, "CHAPTER 5" },
    { { 25, 14 }, 0x0f, "THE HUNTERS" },
    { { 26, 12 }, 0x0e, "CHAPTER 6" },
    { { 26, 14 }, 0x0f, "THE THRONE" },
};

static const sDisplayText text_honey_suckers[] = {
    { { 26, 10 }, 0x07, "Suckers!" },
};

static const sDisplayText text_honey_bible[] = {
    { { 27, 10 }, 0x07, "now face" },
    { { 23, 13 }, 0x0f, "THE ALIEN BIBLE" },
    { { 24, 16 }, 0x0f, "POCKET EDITION" },
};

static const sDisplayText text_honey_rim[] = {
    { { 22, 10 }, 0x07, "Outer rim secured." },
    { { 19, 13 }, 0x07, "Heading back to base..." },
};

static const sDisplayText text_honey_planet[] = {
    { { 18, 10 }, 0x07, "Wait. What is that planet?" },
    { { 20, 13 }, 0x07, "It's not on any chart." },
    { { 16, 16 }, 0x07, "Its surface is all hexagons..." },
    { { 18, 19 }, 0x07, "...like a giant honeycomb." },
};

static const sDisplayText text_honey_command[] = {
    { { 17, 10 }, 0x07, "Command wants a closer look." },
    { { 22, 13 }, 0x07, "Of course they do." },
};

static const sDisplayText text_honey_quiet_0[] = {
    { { 26, 10 }, 0x07, "Strange..." },
    { { 18, 13 }, 0x07, "Not a single ship around." },
};

static const sDisplayText text_honey_quiet_2[] = {
    { { 17, 10 }, 0x07, "Only old wrecks, drifting..." },
    { { 16, 13 }, 0x07, "...all of them sealed in wax." },
};

static const sDisplayText text_honey_quiet_4[] = {
    { { 18, 10 }, 0x07, "Radar picks up something." },
    { { 22, 13 }, 0x07, "A faint buzzing..." },
    { { 23, 16 }, 0x0f, "Bzzzz. Grchkrx!" },
};

static const sDisplayText text_honey_quiet_5[] = {
    { { 18, 10 }, 0x07, "A queen leads the scouts." },
};

static const sDisplayText text_honey_quiet_6[] = {
    { { 19, 10 }, 0x0f, "What the hell was that?!" },
    { { 19, 13 }, 0x07, "And what is that planet?" },
};

static const sDisplayText text_honey_quiet_7[] = {
    { { 22, 10 }, 0x0f, "Oh, the guardian!" },
};

static const sDisplayText text_honey_nursery_0[] = {
    { { 18, 15 }, 0x07, "Small spots on the radar." },
    { { 18, 18 }, 0x07, "They don't look dangerous." },
};

static const sDisplayText text_honey_nursery_orders[] = {
    { { 13, 15 }, 0x0f, "Do NOT shoot. Repeat, do NOT shoot!" },
    { { 24, 18 }, 0x07, "Just observe." },
};

static const sDisplayText text_honey_nursery_1[] = {
    { { 18, 15 }, 0x07, "Something is happening..." },
};

static const sDisplayText text_honey_nursery_2[] = {
    { { 22, 15 }, 0x0f, "Huh? What's that?" },
    { { 21, 18 }, 0x0f, "Some kind of larvae?" },
};

static const sDisplayText text_honey_nursery_3[] = {
    { { 26, 15 }, 0x0c, "Ok, shoot." },
    { { 22, 18 }, 0x0c, "Repeat, DO shoot!" },
};

static const sDisplayText text_honey_nursery_4[] = {
    { { 12, 10 }, 0x07, "Where do all these grubs come from?" },
    { { 11, 13 }, 0x07, "Radar: something big, dripping larvae." },
};

static const sDisplayText text_honey_pod[] = {
    { { 27, 10 }, 0x07, "now face" },
    { { 24, 13 }, 0x0f, "THE BROOD POD" },
};

static const sDisplayText text_honey_hint_pod[] = {
    { { 13, 40 }, 0x0b, "Seal its cells, strike its heart!" },
};

static const sDisplayText text_honey_nursery_6[] = {
    { { 20, 10 }, 0x07, "Phew, that was tough!" },
    { { 11, 13 }, 0x07, "Guardians, larvae, a flying nursery..." },
};

static const sDisplayText text_honey_nursery_7[] = {
    { { 16, 10 }, 0x07, "Anyway, they breed very fast." },
    { { 14, 13 }, 0x07, "This planet could become a problem" },
    { { 19, 15 }, 0x07, "for the whole universe." },
    { { 19, 18 }, 0x0f, "Must investigate deeper." },
};

static const sDisplayText text_honey_wax_cocky[] = {
    { { 23, 10 }, 0x07, "That was easy." },
    { { 20, 13 }, 0x07, "One wave after another" },
    { { 14, 15 }, 0x07, "fodder to my cannons and lasers." },
    { { 24, 18 }, 0x0f, "Piece of cake." },
};

static const sDisplayText text_honey_wax_dumb[] = {
    { { 18, 10 }, 0x07, "No fortifications at all." },
    { { 21, 13 }, 0x0f, "Such a dumb species." },
};

static const sDisplayText text_honey_wax_review_0[] = {
    { { 25, 10 }, 0x07, "Quiet again." },
    { { 16, 13 }, 0x07, "Ok, they know how to fortify." },
    { { 20, 16 }, 0x07, "Anyway, they are dead." },
};

static const sDisplayText text_honey_hunt_3[] = {
    { { 16, 10 }, 0x07, "A lesser queen guards the way" },
    { { 18, 13 }, 0x07, "to the heart of the hive." },
};

static const sDisplayText text_honey_throne_0[] = {
    { { 20, 10 }, 0x07, "The heart of the hive." },
    { { 18, 13 }, 0x07, "The throne of the Empress." },
};

static const sDisplayText text_honey_throne_2[] = {
    { { 13, 10 }, 0x07, "Her guards and workers arrive first." },
};

static const sDisplayText text_honey_empress[] = {
    { { 27, 10 }, 0x07, "now face" },
    { { 21, 13 }, 0x0f, "THE GRCHKRX EMPRESS" },
};

static const sDisplayText text_honey_outro_0[] = {
    { { 19, 10 }, 0x07, "The Empress has fallen." },
    { { 20, 13 }, 0x07, "The hive falls silent." },
    { { 22, 16 }, 0x07, "Mission complete." },
};

static const sDisplayText text_honey_outro_1[] = {
    { { 20, 10 }, 0x07, "But deep in the wax..." },
    { { 15, 13 }, 0x07, "...one tiny grub still wriggles." },
};

static const sDisplayText text_honey_hint_last[] = {
    { { 21, 40 }, 0x0b, "Don't let it hatch!" },
};

static const sDisplayText text_honey_outro_2[] = {
    { { 17, 10 }, 0x07, "The last grub is squashed." },
    { { 22, 13 }, 0x07, "Silence. Finally." },
};

static const sDisplayText text_honey_outro_3[] = {
    { { 15, 10 }, 0x07, "But nobody knows how many eggs" },
    { { 13, 13 }, 0x07, "are hidden out there in the dark..." },
    { { 24, 16 }, 0x07, "...lurking..." },
    { { 25, 19 }, 0x07, "...waiting." },
};

static const sDisplayText text_honey_outro_4[] = {
    { { 27, 16 }, 0x0e, "Bzzzz." },
};

static const sDisplayText text_honey_end[] = {
    { { 27, 16 }, 0x07, "THE END" },
    { { 22, 19 }, 0x07, "Roman Hocke 2026" },
};

// chapter heading - number and title
#define CHAPTER(i)                      (text_honey_chapters + 2 * (i))

// ---------------------------------------------------------------------------
// scenario
// ---------------------------------------------------------------------------

const sScenarioPoint g_scenario_honey[] = {

    // intro screen
    SCPOINT_MACRO_DELAY(1),
    SCPOINT_MACRO_TEXT(text_honey_title, 1, 3),
    SCPOINT_MACRO_TEXT(text_honey_title, 2, 3),
    SCPOINT_MACRO_TEXT(text_honey_title, 3, 12),

    // wait for "hitme" to launch the mission
    { SCPOINT_TYPE_NONE, 3, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT(text_honey_title, 3), &ot_btn_hitme, SCPOINT_EPOS(26, 26) },
    SCPOINT_MACRO_WAIT_DEAD_TEXT(text_honey_title, 3),
    SCPOINT_MACRO_DELAY(4),
    SCPOINT_MACRO_TEXT(text_honey_brief, 1, 5),
    SCPOINT_MACRO_TEXT(text_honey_brief, 2, 5),
    SCPOINT_MACRO_TEXT(text_honey_brief, 3, 5),


    // ==== chapter 1: routine patrol - the usual rabble ======================
    SCPOINT_MACRO_TEXT(CHAPTER(0), 2, 12),

    // octo carousel
    { SCPOINT_TYPE_NONE, 5, 5, scpt_emit_octo, SCPOINT_SUB_TEXT_NONE, NULL, SCPOINT_EPOS(0, 6) },
    SCPOINT_MACRO_WAIT_DEAD(1),

    // more octo carousel
    { SCPOINT_TYPE_NONE, 5, 8, scpt_emit_octo, SCPOINT_SUB_TEXT_NONE, NULL, SCPOINT_EPOS(0, 6) },
    SCPOINT_MACRO_WAIT_DEAD(1),

    // flankers from both sides
    { SCPOINT_TYPE_NONE, 1, 2, scpt_emit_flank_left, SCPOINT_SUB_TEXT_NONE, NULL, SCPOINT_EPOS(0, 0) },
    { SCPOINT_TYPE_NONE, 1, 2, scpt_emit_flank_right, SCPOINT_SUB_TEXT_NONE, NULL, SCPOINT_EPOS(0, 0) },
    SCPOINT_MACRO_WAIT_DEAD(1),

    // both carousels, flankers crossing
    { SCPOINT_TYPE_NONE, 0, 0, scpt_emit_octo, SCPOINT_SUB_TEXT_NONE, NULL, SCPOINT_EPOS(0, 4) },
    { SCPOINT_TYPE_NONE, 5, 0, scpt_emit_octo_right, SCPOINT_SUB_TEXT_NONE, NULL, SCPOINT_EPOS(0, 29) },
    { SCPOINT_TYPE_NONE, 0, 0, scpt_emit_octo, SCPOINT_SUB_TEXT_NONE, NULL, SCPOINT_EPOS(0, 4) },
    { SCPOINT_TYPE_NONE, 5, 0, scpt_emit_octo_right, SCPOINT_SUB_TEXT_NONE, NULL, SCPOINT_EPOS(0, 29) },
    { SCPOINT_TYPE_NONE, 0, 0, scpt_emit_octo, SCPOINT_SUB_TEXT_NONE, NULL, SCPOINT_EPOS(0, 4) },
    { SCPOINT_TYPE_NONE, 5, 0, scpt_emit_octo_right, SCPOINT_SUB_TEXT_NONE, NULL, SCPOINT_EPOS(0, 29) },
    { SCPOINT_TYPE_NONE, 0, 0, scpt_emit_octo, SCPOINT_SUB_TEXT_NONE, NULL, SCPOINT_EPOS(0, 4) },
    { SCPOINT_TYPE_NONE, 5, 0, scpt_emit_octo_right, SCPOINT_SUB_TEXT_NONE, NULL, SCPOINT_EPOS(0, 29) },
    { SCPOINT_TYPE_NONE, 1, 3, scpt_emit_flank_left, SCPOINT_SUB_TEXT_NONE, NULL, SCPOINT_EPOS(0, 0) },
    { SCPOINT_TYPE_NONE, 1, 3, scpt_emit_flank_right, SCPOINT_SUB_TEXT_NONE, NULL, SCPOINT_EPOS(0, 0) },
    SCPOINT_MACRO_WAIT_DEAD(3),

    // the alien bible, travel size
    SCPOINT_MACRO_DELAY(4),
    SCPOINT_MACRO_TEXT(text_honey_bible, 1, 5),
    SCPOINT_MACRO_TEXT(text_honey_bible, 2, 5),
    SCPOINT_MACRO_TEXT(text_honey_bible, 3, 8),
    { SCPOINT_TYPE_NONE, 3, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_alien_bible, SCPOINT_EPOS(23, 10) },
    SCPOINT_MACRO_WAIT_DEAD(3),

    // ==== chapter 2: the quiet - a hive-like planet nobody goes near ========
    SCPOINT_MACRO_DELAY(4),
    SCPOINT_MACRO_TEXT(text_honey_rim, 1, 6),
    SCPOINT_MACRO_TEXT(text_honey_rim, 2, 12),
    { SCPOINT_TYPE_NONE, 6, 0, scpt_emit_random_x, SCPOINT_SUB_TEXT_NONE, &ot_supply, SCPOINT_EPOS(0, 1) },
    SCPOINT_MACRO_DELAY(20),
    SCPOINT_MACRO_TEXT(text_honey_planet, 1, 8),
    SCPOINT_MACRO_TEXT(text_honey_planet, 2, 8),
    SCPOINT_MACRO_TEXT(text_honey_planet, 3, 8),
    SCPOINT_MACRO_TEXT(text_honey_planet, 4, 12),
    SCPOINT_MACRO_TEXT(text_honey_command, 1, 6),
    SCPOINT_MACRO_TEXT(text_honey_command, 2, 10),
    SCPOINT_MACRO_DELAY(8),

    SCPOINT_MACRO_TEXT(CHAPTER(1), 2, 12),

    // nothing at all, just the texts and silence
    SCPOINT_MACRO_DELAY(16),
    SCPOINT_MACRO_TEXT(text_honey_quiet_0, 1, 6),
    SCPOINT_MACRO_TEXT(text_honey_quiet_0, 2, 12),
    SCPOINT_MACRO_DELAY(16),
    SCPOINT_MACRO_TEXT(text_honey_quiet_2, 1, 8),
    SCPOINT_MACRO_TEXT(text_honey_quiet_2, 2, 14),
    SCPOINT_MACRO_DELAY(16),
    SCPOINT_MACRO_TEXT(text_honey_quiet_4, 1, 6),
    SCPOINT_MACRO_TEXT(text_honey_quiet_4, 2, 8),
    SCPOINT_MACRO_TEXT(text_honey_quiet_4, 3, 6),

    // the hive's outer scouts
    { SCPOINT_TYPE_NONE, 4, 2, scpt_emit_at_pos, SCPOINT_SUB_TEXT(text_honey_quiet_4 + 2, 1), &ot_grchkrx_bee, SCPOINT_EPOS_LEFT(8) },
    SCPOINT_MACRO_DELAY(6),
    { SCPOINT_TYPE_NONE, 3, 3, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_RIGHT(12) },
    { SCPOINT_TYPE_NONE, 3, 3, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_LEFT(4) },
    SCPOINT_MACRO_WAIT_DEAD(3),

    // scouts' queen guarded by bees from both sides, more raining after
    SCPOINT_MACRO_DELAY(4),
    { SCPOINT_TYPE_NONE, 6, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT(text_honey_quiet_5, 1), &ot_grchkrx_queen, SCPOINT_EPOS(26, 0) },
    { SCPOINT_TYPE_NONE, 2, 5, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_LEFT(12) },
    { SCPOINT_TYPE_NONE, 2, 5, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_RIGHT(16) },
    { SCPOINT_TYPE_NONE, 2, 5, scpt_emit_random_x, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS(0, 1) },
    SCPOINT_MACRO_WAIT_DEAD(3),

    // catching breath after the first encounter
    SCPOINT_MACRO_DELAY(4),
    SCPOINT_MACRO_TEXT(text_honey_quiet_6, 1, 8),
    SCPOINT_MACRO_TEXT(text_honey_quiet_6, 2, 12),

    // ==== chapter 3: the nursery - larvae ===================================
    SCPOINT_MACRO_DELAY(4),
    SCPOINT_MACRO_TEXT(CHAPTER(2), 2, 12),
    SCPOINT_MACRO_TEXT(text_honey_nursery_0, 1, 6),
    SCPOINT_MACRO_TEXT(text_honey_nursery_0, 2, 20),

    // two grubs to watch (1 s apart), texts following the life of the first
    // one - a point lasts (delay + 1) / 4 s each round, so the pupa comes at
    // 7.5 s, wings at 9.25 s, hatching at 10 s, and the order to shoot 1 s
    // later; the order not to shoot comes 2.5 s ahead, so the player stops
    // firing in time, and the screen stays clear for watching the crawling
    SCPOINT_MACRO_TEXT(text_honey_nursery_orders, 1, 11),
    SCPOINT_MACRO_TEXT(text_honey_nursery_orders, 2, 5),
    SCPOINT_MACRO_DELAY(5),
    { SCPOINT_TYPE_NONE, 3, 2, scpt_emit_random_x, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_larva, SCPOINT_EPOS(0, 6) },
    SCPOINT_MACRO_DELAY(17),
    SCPOINT_MACRO_TEXT(text_honey_nursery_1, 1, 7),
    SCPOINT_MACRO_TEXT(text_honey_nursery_2, 2, 11),
    SCPOINT_MACRO_TEXT(text_honey_nursery_3, 2, 9),

    // right after the order more grubs come, while the first bees still fly,
    // then a brood with guards
    { SCPOINT_TYPE_NONE, 3, 8, scpt_emit_random_x, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_larva, SCPOINT_EPOS(0, 4) },
    SCPOINT_MACRO_DELAY(10),
    { SCPOINT_TYPE_NONE, 6, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT(text_honey_quiet_7, 1), &ot_grchkrx_queen, SCPOINT_EPOS(26, 0) },
    SCPOINT_MACRO_WAIT_DEAD(3),
    SCPOINT_MACRO_DELAY(4),
    { SCPOINT_TYPE_NONE, 1, 5, scpt_emit_random_x, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_larva, SCPOINT_EPOS(0, 6) },
    { SCPOINT_TYPE_NONE, 1, 8, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_RIGHT(20) },
    SCPOINT_MACRO_WAIT_DEAD(3),

    // two queens with a swarm of bees down low, the brood hatching around them
    SCPOINT_MACRO_DELAY(4),
    { SCPOINT_TYPE_NONE, 4, 0, scpt_emit_mirrored, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_queen, SCPOINT_EPOS(6, 0) },
    { SCPOINT_TYPE_NONE, 1, 4, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_LEFT(22) },
    { SCPOINT_TYPE_NONE, 1, 4, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_RIGHT(26) },
    SCPOINT_MACRO_DELAY(11),
    { SCPOINT_TYPE_NONE, 1, 7, scpt_emit_random_x, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_larva, SCPOINT_EPOS(0, 8) },
    SCPOINT_MACRO_WAIT_DEAD(3),

    // the brood pod - a flying nursery, the hint shown for its first seconds
    SCPOINT_MACRO_DELAY(4),
    SCPOINT_MACRO_TEXT(text_honey_nursery_4, 1, 6),
    SCPOINT_MACRO_TEXT(text_honey_nursery_4, 2, 10),
    SCPOINT_MACRO_TEXT(text_honey_pod, 1, 4),
    SCPOINT_MACRO_TEXT(text_honey_pod, 2, 6),
    { SCPOINT_TYPE_NONE, 24, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT(text_honey_hint_pod, 1), &ot_grchkrx_pod, SCPOINT_EPOS(20, 2) },
    SCPOINT_MACRO_WAIT_DEAD(3),

    // what the pilot makes of it
    SCPOINT_MACRO_DELAY(4),
    SCPOINT_MACRO_TEXT(text_honey_nursery_6, 1, 8),
    SCPOINT_MACRO_TEXT(text_honey_nursery_6, 2, 12),
    SCPOINT_MACRO_TEXT(text_honey_nursery_7, 1, 8),
    SCPOINT_MACRO_TEXT(text_honey_nursery_7, 3, 10),
    SCPOINT_MACRO_TEXT(text_honey_nursery_7, 4, 12),
    { SCPOINT_TYPE_NONE, 6, 0, scpt_emit_random_x, SCPOINT_SUB_TEXT_NONE, &ot_supply, SCPOINT_EPOS(0, 1) },
    SCPOINT_MACRO_DELAY(20),

    // ==== chapter 4: knee-deep in honey - builders ==========================
    SCPOINT_MACRO_TEXT(CHAPTER(3), 2, 12),

    // plain bees first - from one side, then the other
    { SCPOINT_TYPE_NONE, 1, 4, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_LEFT(6) },
    { SCPOINT_TYPE_NONE, 2, 4, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_RIGHT(14) },
    SCPOINT_MACRO_WAIT_DEAD(3),

    // bees raining from random places
    { SCPOINT_TYPE_NONE, 2, 9, scpt_emit_random_x, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS(0, 1) },
    SCPOINT_MACRO_WAIT_DEAD(3),

    // the pilot is getting cocky
    SCPOINT_MACRO_TEXT(text_honey_wax_cocky, 1, 6),
    SCPOINT_MACRO_TEXT(text_honey_wax_cocky, 3, 8),
    SCPOINT_MACRO_TEXT(text_honey_wax_cocky, 4, 10),

    // three streams at three heights
    { SCPOINT_TYPE_NONE, 1, 5, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_LEFT(4) },
    { SCPOINT_TYPE_NONE, 1, 5, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_RIGHT(12) },
    { SCPOINT_TYPE_NONE, 1, 5, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_LEFT(20) },
    SCPOINT_MACRO_WAIT_DEAD(3),
    SCPOINT_MACRO_DELAY(4),
    SCPOINT_MACRO_TEXT(text_honey_wax_dumb, 1, 6),
    SCPOINT_MACRO_TEXT(text_honey_wax_dumb, 2, 10),

    // two workers and the first wall
    { SCPOINT_TYPE_NONE, 14, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_builder, SCPOINT_EPOS_LEFT(16) },
    { SCPOINT_TYPE_NONE, 14, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_builder, SCPOINT_EPOS_RIGHT(16) },
    SCPOINT_MACRO_WAIT_DEAD(3),
    SCPOINT_MACRO_DELAY(8),

    // workers mending the wall bees hide behind
    { SCPOINT_TYPE_NONE, 14, 1, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_builder, SCPOINT_EPOS_LEFT(16) },
    { SCPOINT_TYPE_NONE, 14, 1, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_builder, SCPOINT_EPOS_RIGHT(16) },
    { SCPOINT_TYPE_NONE, 3, 8, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_LEFT(2) },
    SCPOINT_MACRO_DELAY(12),

    // walled nursery - two layers of wax, grubs crawling behind
    { SCPOINT_TYPE_NONE, 4, 8, scpt_emit_random_x, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_larva, SCPOINT_EPOS(0, 2) },
    SCPOINT_MACRO_DELAY(20),
    { SCPOINT_TYPE_NONE, 4, 0, scpt_emit_mirrored, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_queen, SCPOINT_EPOS(6, 0) },
    { SCPOINT_TYPE_NONE, 3, 8, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_RIGHT(2) },
    SCPOINT_MACRO_WAIT_DEAD(3),
    SCPOINT_MACRO_DELAY(4),

    // more workers than room on the wall (plates at row 11) - every broken
    // plate gets replaced from the spares, grubs crawling behind, bees raining
    { SCPOINT_TYPE_NONE, 6, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_builder, SCPOINT_EPOS_LEFT(8) },
    { SCPOINT_TYPE_NONE, 6, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_builder, SCPOINT_EPOS_RIGHT(8) },
    { SCPOINT_TYPE_NONE, 6, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_builder, SCPOINT_EPOS_LEFT(8) },
    { SCPOINT_TYPE_NONE, 10, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_builder, SCPOINT_EPOS_RIGHT(8) },
    { SCPOINT_TYPE_NONE, 4, 5, scpt_emit_random_x, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_larva, SCPOINT_EPOS(0, 1) },
    { SCPOINT_TYPE_NONE, 2, 5, scpt_emit_random_x, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS(0, 1) },
    SCPOINT_MACRO_WAIT_DEAD(3),
    SCPOINT_MACRO_DELAY(4),

    // the wax fortress - two walls (plates at rows 8 and 17) rising first,
    // then a queen and her brood behind them, bees raining through the gaps
    // and late workers coming to reinforce both walls
    { SCPOINT_TYPE_NONE, 2, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_builder, SCPOINT_EPOS_LEFT(5) },
    { SCPOINT_TYPE_NONE, 2, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_builder, SCPOINT_EPOS_RIGHT(5) },
    { SCPOINT_TYPE_NONE, 2, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_builder, SCPOINT_EPOS_LEFT(14) },
    { SCPOINT_TYPE_NONE, 14, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_builder, SCPOINT_EPOS_RIGHT(14) },
    { SCPOINT_TYPE_NONE, 4, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_queen, SCPOINT_EPOS(26, 0) },
    { SCPOINT_TYPE_NONE, 4, 5, scpt_emit_random_x, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_larva, SCPOINT_EPOS(0, 1) },
    { SCPOINT_TYPE_NONE, 3, 7, scpt_emit_random_x, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS(0, 1) },
    { SCPOINT_TYPE_NONE, 12, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_builder, SCPOINT_EPOS_LEFT(5) },
    { SCPOINT_TYPE_NONE, 0, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_builder, SCPOINT_EPOS_RIGHT(14) },
    SCPOINT_MACRO_WAIT_DEAD(3),

    // looking back at the wax
    SCPOINT_MACRO_TEXT(text_honey_wax_review_0, 1, 6),
    SCPOINT_MACRO_TEXT(text_honey_wax_review_0, 2, 8),
    SCPOINT_MACRO_TEXT(text_honey_wax_review_0, 3, 10),
    { SCPOINT_TYPE_NONE, 6, 0, scpt_emit_random_x, SCPOINT_SUB_TEXT_NONE, &ot_supply, SCPOINT_EPOS(0, 1) },
    SCPOINT_MACRO_DELAY(12),

    // ==== chapter 5: the hunters - stingers =================================
    SCPOINT_MACRO_TEXT(CHAPTER(4), 2, 12),

    // lone group of late bees
    { SCPOINT_TYPE_NONE, 2, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_LEFT(8) },
    { SCPOINT_TYPE_NONE, 2, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_RIGHT(12) },
    { SCPOINT_TYPE_NONE, 2, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_LEFT(16) },
    { SCPOINT_TYPE_NONE, 2, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_RIGHT(20) },
    { SCPOINT_TYPE_NONE, 2, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_LEFT(24) },
    SCPOINT_MACRO_WAIT_DEAD(1),

    // a lone hunter, then a pack at different heights
    { SCPOINT_TYPE_NONE, 1, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS(28, 4) },
    SCPOINT_MACRO_WAIT_DEAD(1),
    { SCPOINT_TYPE_NONE, 6, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS_LEFT(2) },
    { SCPOINT_TYPE_NONE, 6, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS(28, 6) },
    { SCPOINT_TYPE_NONE, 1, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS_RIGHT(10) },
    SCPOINT_MACRO_WAIT_DEAD(1),

    // hunters over the brood - grubs crawling low while a pair of stingers
    // keeps diving, it's either the hunters or the hatching
    { SCPOINT_TYPE_NONE, 2, 5, scpt_emit_random_x, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_larva, SCPOINT_EPOS(0, 14) },
    { SCPOINT_TYPE_NONE, 0, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS_LEFT(3) },
    { SCPOINT_TYPE_NONE, 1, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS_RIGHT(7) },
    SCPOINT_MACRO_WAIT_DEAD(1),

    // bigger group of stingers
    { SCPOINT_TYPE_NONE, 4, 8, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS_LEFT(10) },
    { SCPOINT_TYPE_NONE, 4, 8, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS_RIGHT(4) },
    SCPOINT_MACRO_WAIT_DEAD(1),

    // combined stingers and bees
    { SCPOINT_TYPE_NONE, 3, 2, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS_LEFT(10) },
    { SCPOINT_TYPE_NONE, 3, 2, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS_RIGHT(4) },
    { SCPOINT_TYPE_NONE, 2, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_LEFT(8) },
    { SCPOINT_TYPE_NONE, 2, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_RIGHT(12) },
    { SCPOINT_TYPE_NONE, 2, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_LEFT(16) },
    { SCPOINT_TYPE_NONE, 2, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_RIGHT(20) },
    { SCPOINT_TYPE_NONE, 2, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_LEFT(24) },
    SCPOINT_MACRO_WAIT_DEAD(1),

    // hunters behind the wax, bees joining
    { SCPOINT_TYPE_NONE, 4, 1, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_builder, SCPOINT_EPOS_LEFT(20) },
    { SCPOINT_TYPE_NONE, 12, 1, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_builder, SCPOINT_EPOS_RIGHT(20) },
    { SCPOINT_TYPE_NONE, 4, 4, scpt_emit_random_x, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS(0, 1) },
    { SCPOINT_TYPE_NONE, 3, 4, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_RIGHT(2) },
    { SCPOINT_TYPE_NONE, 3, 4, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS_LEFT(2) },
    SCPOINT_MACRO_WAIT_DEAD(3),
    SCPOINT_MACRO_TEXT(text_honey_suckers, 1, 8),

    // the hunt escalating - a stream from one side, then streams from both
    // sides at once, then stingers dropping anywhere with bees following,
    // each one starting before the previous is cleared
    { SCPOINT_TYPE_NONE, 4, 8, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS_LEFT(5) },
    SCPOINT_MACRO_DELAY(20),
    { SCPOINT_TYPE_NONE, 0, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS_LEFT(10) },
    { SCPOINT_TYPE_NONE, 5, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS_RIGHT(14) },
    { SCPOINT_TYPE_NONE, 0, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS_LEFT(10) },
    { SCPOINT_TYPE_NONE, 5, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS_RIGHT(14) },
    { SCPOINT_TYPE_NONE, 0, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS_LEFT(10) },
    { SCPOINT_TYPE_NONE, 5, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS_RIGHT(14) },
    { SCPOINT_TYPE_NONE, 0, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS_LEFT(10) },
    { SCPOINT_TYPE_NONE, 5, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS_RIGHT(14) },
    { SCPOINT_TYPE_NONE, 0, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS_LEFT(10) },
    { SCPOINT_TYPE_NONE, 5, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS_RIGHT(14) },
    SCPOINT_MACRO_DELAY(16),
    { SCPOINT_TYPE_NONE, 3, 9, scpt_emit_random_x, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS(0, 1) },
    { SCPOINT_TYPE_NONE, 2, 7, scpt_emit_random_x, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_bee, SCPOINT_EPOS(0, 1) },
    SCPOINT_MACRO_WAIT_DEAD(3),

    // lesser queen with her brood and hunters
    SCPOINT_MACRO_TEXT(text_honey_hunt_3, 1, 6),
    SCPOINT_MACRO_TEXT(text_honey_hunt_3, 2, 8),
    { SCPOINT_TYPE_NONE, 8, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_queen, SCPOINT_EPOS(26, 1) },
    { SCPOINT_TYPE_NONE, 6, 2, scpt_emit_random_x, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_larva, SCPOINT_EPOS(0, 8) },
    { SCPOINT_TYPE_NONE, 8, 1, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS_LEFT(6) },
    SCPOINT_MACRO_WAIT_DEAD(3),

    // healery before the throne
    { SCPOINT_TYPE_NONE, 5, 1, scpt_emit_random_x, SCPOINT_SUB_TEXT_NONE, &ot_supply, SCPOINT_EPOS(0, 1) },
    SCPOINT_MACRO_DELAY(16),

    // ==== chapter 6: the throne - empress ===================================
    SCPOINT_MACRO_TEXT(CHAPTER(5), 2, 12),
    SCPOINT_MACRO_TEXT(text_honey_throne_0, 1, 6),
    SCPOINT_MACRO_TEXT(text_honey_throne_0, 2, 10),
    SCPOINT_MACRO_TEXT(text_honey_throne_2, 1, 6),

    // stingers keep the player busy while builders wall her in (three
    // layers, plates at rows 12, 16 and 20), then she arrives
    { SCPOINT_TYPE_NONE, 2, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS(14, 4) },
    { SCPOINT_TYPE_NONE, 4, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS(42, 6) },
    { SCPOINT_TYPE_NONE, 2, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_builder, SCPOINT_EPOS_LEFT(9) },
    { SCPOINT_TYPE_NONE, 4, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_builder, SCPOINT_EPOS_RIGHT(9) },
    { SCPOINT_TYPE_NONE, 2, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_builder, SCPOINT_EPOS_LEFT(14) },
    { SCPOINT_TYPE_NONE, 4, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_builder, SCPOINT_EPOS_RIGHT(14) },
    { SCPOINT_TYPE_NONE, 2, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS(28, 3) },
    { SCPOINT_TYPE_NONE, 2, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_builder, SCPOINT_EPOS_LEFT(19) },
    { SCPOINT_TYPE_NONE, 12, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_builder, SCPOINT_EPOS_RIGHT(19) },
    { SCPOINT_TYPE_NONE, 8, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT_NONE, &ot_grchkrx_stinger, SCPOINT_EPOS_LEFT(5) },
    SCPOINT_MACRO_TEXT(text_honey_empress, 1, 4),
    SCPOINT_MACRO_TEXT(text_honey_empress, 2, 4),
    { SCPOINT_TYPE_NONE, 3, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT(text_honey_empress, 2), &ot_grchkrx_empress, SCPOINT_EPOS(24, 1) },
    SCPOINT_MACRO_WAIT_DEAD(3),

    // ==== outro =============================================================
    SCPOINT_MACRO_DELAY(8),
    SCPOINT_MACRO_TEXT(text_honey_outro_0, 1, 7),
    SCPOINT_MACRO_TEXT(text_honey_outro_0, 2, 7),
    SCPOINT_MACRO_TEXT(text_honey_outro_0, 3, 7),

    { SCPOINT_TYPE_NONE, 3, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT(text_honey_outro_0, 3), &ot_btn_hitme, SCPOINT_EPOS(26, 26) },
    SCPOINT_MACRO_WAIT_DEAD_TEXT(text_honey_outro_0, 3),

    SCPOINT_MACRO_TEXT(text_honey_outro_1, 1, 7),
    SCPOINT_MACRO_TEXT(text_honey_outro_1, 2, 10),

    // the last grub of the hive, squash it (or its bee) to finish
    { SCPOINT_TYPE_NONE, 3, 0, scpt_emit_at_pos, SCPOINT_SUB_TEXT(text_honey_hint_last, 1), &ot_grchkrx_larva, SCPOINT_EPOS(27, 16) },
    SCPOINT_MACRO_WAIT_DEAD_TEXT(text_honey_hint_last, 1),

    // or was it the last one?
    SCPOINT_MACRO_DELAY(4),
    SCPOINT_MACRO_TEXT(text_honey_outro_2, 1, 6),
    SCPOINT_MACRO_TEXT(text_honey_outro_2, 2, 10),
    SCPOINT_MACRO_TEXT(text_honey_outro_3, 1, 6),
    SCPOINT_MACRO_TEXT(text_honey_outro_3, 2, 8),
    SCPOINT_MACRO_TEXT(text_honey_outro_3, 3, 6),
    SCPOINT_MACRO_TEXT(text_honey_outro_3, 4, 12),
    SCPOINT_MACRO_DELAY(8),
    SCPOINT_MACRO_TEXT(text_honey_outro_4, 1, 8),
    SCPOINT_MACRO_DELAY(4),

    // the end
    { SCPOINT_TYPE_END, 1, 1, NULL, SCPOINT_SUB_TEXT(text_honey_end, 2), NULL, { 0, 0 } },
};

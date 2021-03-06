#ifndef slic3r_PrintConfig_hpp_
#define slic3r_PrintConfig_hpp_

#include "Config.hpp"

namespace Slic3r {

enum GCodeFlavor {
    gcfRepRap, gcfTeacup, gcfMakerWare, gcfSailfish, gcfMach3, gcfNoExtrusion,
};

enum InfillPattern {
    ipRectilinear, ipLine, ipConcentric, ipHoneycomb,
    ipHilbertCurve, ipArchimedeanChords, ipOctagramSpiral,
};

enum SupportMaterialPattern {
    smpRectilinear, smpRectilinearGrid, smpHoneycomb, smpPillars,
};

template<> inline t_config_enum_values ConfigOptionEnum<GCodeFlavor>::get_enum_values() {
    t_config_enum_values keys_map;
    keys_map["reprap"]          = gcfRepRap;
    keys_map["teacup"]          = gcfTeacup;
    keys_map["makerware"]       = gcfMakerWare;
    keys_map["sailfish"]        = gcfSailfish;
    keys_map["mach3"]           = gcfMach3;
    keys_map["no-extrusion"]    = gcfNoExtrusion;
    return keys_map;
}

template<> inline t_config_enum_values ConfigOptionEnum<InfillPattern>::get_enum_values() {
    t_config_enum_values keys_map;
    keys_map["rectilinear"]         = ipRectilinear;
    keys_map["line"]                = ipLine;
    keys_map["concentric"]          = ipConcentric;
    keys_map["honeycomb"]           = ipHoneycomb;
    keys_map["hilbertcurve"]        = ipHilbertCurve;
    keys_map["archimedeanchords"]   = ipArchimedeanChords;
    keys_map["octagramspiral"]      = ipOctagramSpiral;
    return keys_map;
}

template<> inline t_config_enum_values ConfigOptionEnum<SupportMaterialPattern>::get_enum_values() {
    t_config_enum_values keys_map;
    keys_map["rectilinear"]         = smpRectilinear;
    keys_map["rectilinear-grid"]    = smpRectilinearGrid;
    keys_map["honeycomb"]           = smpHoneycomb;
    keys_map["pillars"]             = smpPillars;
    return keys_map;
}

class PrintConfigDef
{
    public:
    static t_optiondef_map def;
    
    static t_optiondef_map build_def () {
        t_optiondef_map Options;
        
        Options["avoid_crossing_perimeters"].type = coBool;
        Options["avoid_crossing_perimeters"].label = "Avoid crossing perimeters";
        Options["avoid_crossing_perimeters"].tooltip = "Optimize travel moves in order to minimize the crossing of perimeters. This is mostly useful with Bowden extruders which suffer from oozing. This feature slows down both the print and the G-code generation.";
        Options["avoid_crossing_perimeters"].cli = "avoid-crossing-perimeters!";

        Options["bed_size"].type = coPoint;
        Options["bed_size"].label = "Bed size";
        Options["bed_size"].tooltip = "Size of your bed. This is used to adjust the preview in the plater and for auto-arranging parts in it.";
        Options["bed_size"].sidetext = "mm";
        Options["bed_size"].cli = "bed-size=s";

        Options["bed_temperature"].type = coInt;
        Options["bed_temperature"].label = "Other layers";
        Options["bed_temperature"].tooltip = "Bed temperature for layers after the first one. Set this to zero to disable bed temperature control commands in the output.";
        Options["bed_temperature"].sidetext = "°C";
        Options["bed_temperature"].cli = "bed-temperature=i";
        Options["bed_temperature"].full_label = "Bed temperature";
        Options["bed_temperature"].max = 300;

        Options["bottom_solid_layers"].type = coInt;
        Options["bottom_solid_layers"].label = "Bottom";
        Options["bottom_solid_layers"].category = "Layers and Perimeters";
        Options["bottom_solid_layers"].tooltip = "Number of solid layers to generate on bottom surfaces.";
        Options["bottom_solid_layers"].cli = "bottom-solid-layers=i";
        Options["bottom_solid_layers"].full_label = "Bottom solid layers";

        Options["bridge_acceleration"].type = coFloat;
        Options["bridge_acceleration"].label = "Bridge";
        Options["bridge_acceleration"].tooltip = "This is the acceleration your printer will use for bridges. Set zero to disable acceleration control for bridges.";
        Options["bridge_acceleration"].sidetext = "mm/s²";
        Options["bridge_acceleration"].cli = "bridge-acceleration=f";

        Options["bridge_fan_speed"].type = coInt;
        Options["bridge_fan_speed"].label = "Bridges fan speed";
        Options["bridge_fan_speed"].tooltip = "This fan speed is enforced during all bridges and overhangs.";
        Options["bridge_fan_speed"].sidetext = "%";
        Options["bridge_fan_speed"].cli = "bridge-fan-speed=i";
        Options["bridge_fan_speed"].max = 100;

        Options["bridge_flow_ratio"].type = coFloat;
        Options["bridge_flow_ratio"].label = "Bridge flow ratio";
        Options["bridge_flow_ratio"].tooltip = "This factor affects the amount of plastic for bridging. You can decrease it slightly to pull the extrudates and prevent sagging, although default settings are usually good and you should experiment with cooling (use a fan) before tweaking this.";
        Options["bridge_flow_ratio"].cli = "bridge-flow-ratio=f";

        Options["bridge_speed"].type = coFloat;
        Options["bridge_speed"].label = "Bridges";
        Options["bridge_speed"].tooltip = "Speed for printing bridges.";
        Options["bridge_speed"].sidetext = "mm/s";
        Options["bridge_speed"].cli = "bridge-speed=f";
        Options["bridge_speed"].aliases.push_back("bridge_feed_rate");

        Options["brim_width"].type = coFloat;
        Options["brim_width"].label = "Brim width";
        Options["brim_width"].tooltip = "Horizontal width of the brim that will be printed around each object on the first layer.";
        Options["brim_width"].sidetext = "mm";
        Options["brim_width"].cli = "brim-width=f";

        Options["complete_objects"].type = coBool;
        Options["complete_objects"].label = "Complete individual objects";
        Options["complete_objects"].tooltip = "When printing multiple objects or copies, this feature will complete each object before moving onto next one (and starting it from its bottom layer). This feature is useful to avoid the risk of ruined prints. Slic3r should warn and prevent you from extruder collisions, but beware.";
        Options["complete_objects"].cli = "complete-objects!";

        Options["cooling"].type = coBool;
        Options["cooling"].label = "Enable auto cooling";
        Options["cooling"].tooltip = "This flag enables the automatic cooling logic that adjusts print speed and fan speed according to layer printing time.";
        Options["cooling"].cli = "cooling!";

        Options["default_acceleration"].type = coFloat;
        Options["default_acceleration"].label = "Default";
        Options["default_acceleration"].tooltip = "This is the acceleration your printer will be reset to after the role-specific acceleration values are used (perimeter/infill). Set zero to prevent resetting acceleration at all.";
        Options["default_acceleration"].sidetext = "mm/s²";
        Options["default_acceleration"].cli = "default-acceleration=f";

        Options["disable_fan_first_layers"].type = coInt;
        Options["disable_fan_first_layers"].label = "Disable fan for the first";
        Options["disable_fan_first_layers"].tooltip = "You can set this to a positive value to disable fan at all during the first layers, so that it does not make adhesion worse.";
        Options["disable_fan_first_layers"].sidetext = "layers";
        Options["disable_fan_first_layers"].cli = "disable-fan-first-layers=i";
        Options["disable_fan_first_layers"].max = 1000;

        Options["duplicate_distance"].type = coFloat;
        Options["duplicate_distance"].label = "Distance between copies";
        Options["duplicate_distance"].tooltip = "Distance used for the auto-arrange feature of the plater.";
        Options["duplicate_distance"].sidetext = "mm";
        Options["duplicate_distance"].cli = "duplicate-distance=f";
        Options["duplicate_distance"].aliases.push_back("multiply_distance");

        Options["end_gcode"].type = coString;
        Options["end_gcode"].label = "End G-code";
        Options["end_gcode"].tooltip = "This end procedure is inserted at the end of the output file. Note that you can use placeholder variables for all Slic3r settings.";
        Options["end_gcode"].cli = "end-gcode=s";
        Options["end_gcode"].multiline = true;
        Options["end_gcode"].full_width = true;
        Options["end_gcode"].height = 120;

        Options["external_perimeter_speed"].type = coFloatOrPercent;
        Options["external_perimeter_speed"].label = "External perimeters";
        Options["external_perimeter_speed"].tooltip = "This separate setting will affect the speed of external perimeters (the visible ones). If expressed as percentage (for example: 80%) it will be calculated on the perimeters speed setting above.";
        Options["external_perimeter_speed"].sidetext = "mm/s or %";
        Options["external_perimeter_speed"].cli = "external-perimeter-speed=s";
        Options["external_perimeter_speed"].ratio_over = "perimeter_speed";

        Options["external_perimeters_first"].type = coBool;
        Options["external_perimeters_first"].label = "External perimeters first";
        Options["external_perimeters_first"].tooltip = "Print contour perimeters from the outermost one to the innermost one instead of the default inverse order.";
        Options["external_perimeters_first"].cli = "external-perimeters-first!";

        Options["extra_perimeters"].type = coBool;
        Options["extra_perimeters"].label = "Extra perimeters if needed";
        Options["extra_perimeters"].category = "Layers and Perimeters";
        Options["extra_perimeters"].tooltip = "Add more perimeters when needed for avoiding gaps in sloping walls.";
        Options["extra_perimeters"].cli = "extra-perimeters!";

        Options["extruder"].type = coInt;
        Options["extruder"].label = "Extruder";
        Options["extruder"].cli = "extruder=i";
        Options["extruder"].shortcut.push_back("perimeter_extruder");
        Options["extruder"].shortcut.push_back("infill_extruder");
        Options["extruder"].shortcut.push_back("support_material_extruder");
        Options["extruder"].shortcut.push_back("support_material_interface_extruder");

        Options["extruder_clearance_height"].type = coFloat;
        Options["extruder_clearance_height"].label = "Height";
        Options["extruder_clearance_height"].tooltip = "Set this to the vertical distance between your nozzle tip and (usually) the X carriage rods. In other words, this is the height of the clearance cylinder around your extruder, and it represents the maximum depth the extruder can peek before colliding with other printed objects.";
        Options["extruder_clearance_height"].sidetext = "mm";
        Options["extruder_clearance_height"].cli = "extruder-clearance-height=f";

        Options["extruder_clearance_radius"].type = coFloat;
        Options["extruder_clearance_radius"].label = "Radius";
        Options["extruder_clearance_radius"].tooltip = "Set this to the clearance radius around your extruder. If the extruder is not centered, choose the largest value for safety. This setting is used to check for collisions and to display the graphical preview in the plater.";
        Options["extruder_clearance_radius"].sidetext = "mm";
        Options["extruder_clearance_radius"].cli = "extruder-clearance-radius=f";

        Options["extruder_offset"].type = coPoints;
        Options["extruder_offset"].label = "Extruder offset";
        Options["extruder_offset"].tooltip = "If your firmware doesn't handle the extruder displacement you need the G-code to take it into account. This option lets you specify the displacement of each extruder with respect to the first one. It expects positive coordinates (they will be subtracted from the XY coordinate).";
        Options["extruder_offset"].sidetext = "mm";
        Options["extruder_offset"].cli = "extruder-offset=s@";

        Options["extrusion_axis"].type = coString;
        Options["extrusion_axis"].label = "Extrusion axis";
        Options["extrusion_axis"].tooltip = "Use this option to set the axis letter associated to your printer's extruder (usually E but some printers use A).";
        Options["extrusion_axis"].cli = "extrusion-axis=s";

        Options["extrusion_multiplier"].type = coFloats;
        Options["extrusion_multiplier"].label = "Extrusion multiplier";
        Options["extrusion_multiplier"].tooltip = "This factor changes the amount of flow proportionally. You may need to tweak this setting to get nice surface finish and correct single wall widths. Usual values are between 0.9 and 1.1. If you think you need to change this more, check filament diameter and your firmware E steps.";
        Options["extrusion_multiplier"].cli = "extrusion-multiplier=f@";

        Options["extrusion_width"].type = coFloatOrPercent;
        Options["extrusion_width"].label = "Default extrusion width";
        Options["extrusion_width"].category = "Extrusion Width";
        Options["extrusion_width"].tooltip = "Set this to a non-zero value to set a manual extrusion width. If left to zero, Slic3r calculates a width automatically. If expressed as percentage (for example: 230%) it will be computed over layer height.";
        Options["extrusion_width"].sidetext = "mm or % (leave 0 for auto)";
        Options["extrusion_width"].cli = "extrusion-width=s";

        Options["fan_always_on"].type = coBool;
        Options["fan_always_on"].label = "Keep fan always on";
        Options["fan_always_on"].tooltip = "If this is enabled, fan will never be disabled and will be kept running at least at its minimum speed. Useful for PLA, harmful for ABS.";
        Options["fan_always_on"].cli = "fan-always-on!";

        Options["fan_below_layer_time"].type = coInt;
        Options["fan_below_layer_time"].label = "Enable fan if layer print time is below";
        Options["fan_below_layer_time"].tooltip = "If layer print time is estimated below this number of seconds, fan will be enabled and its speed will be calculated by interpolating the minimum and maximum speeds.";
        Options["fan_below_layer_time"].sidetext = "approximate seconds";
        Options["fan_below_layer_time"].cli = "fan-below-layer-time=i";
        Options["fan_below_layer_time"].width = 60;
        Options["fan_below_layer_time"].max = 1000;

        Options["filament_diameter"].type = coFloats;
        Options["filament_diameter"].label = "Diameter";
        Options["filament_diameter"].tooltip = "Enter your filament diameter here. Good precision is required, so use a caliper and do multiple measurements along the filament, then compute the average.";
        Options["filament_diameter"].sidetext = "mm";
        Options["filament_diameter"].cli = "filament-diameter=f@";

        Options["fill_angle"].type = coInt;
        Options["fill_angle"].label = "Fill angle";
        Options["fill_angle"].category = "Infill";
        Options["fill_angle"].tooltip = "Default base angle for infill orientation. Cross-hatching will be applied to this. Bridges will be infilled using the best direction Slic3r can detect, so this setting does not affect them.";
        Options["fill_angle"].sidetext = "°";
        Options["fill_angle"].cli = "fill-angle=i";
        Options["fill_angle"].max = 359;

        Options["fill_density"].type = coFloat;
        Options["fill_density"].label = "Fill density";
        Options["fill_density"].category = "Infill";
        Options["fill_density"].tooltip = "Density of internal infill, expressed in the range 0 - 1.";
        Options["fill_density"].cli = "fill-density=f";

        Options["fill_pattern"].type = coEnum;
        Options["fill_pattern"].label = "Fill pattern";
        Options["fill_pattern"].category = "Infill";
        Options["fill_pattern"].tooltip = "Fill pattern for general low-density infill.";
        Options["fill_pattern"].cli = "fill-pattern=s";
        Options["fill_pattern"].enum_keys_map = ConfigOptionEnum<InfillPattern>::get_enum_values();
        Options["fill_pattern"].enum_values.push_back("rectilinear");
        Options["fill_pattern"].enum_values.push_back("line");
        Options["fill_pattern"].enum_values.push_back("concentric");
        Options["fill_pattern"].enum_values.push_back("honeycomb");
        Options["fill_pattern"].enum_values.push_back("hilbertcurve");
        Options["fill_pattern"].enum_values.push_back("archimedeanchords");
        Options["fill_pattern"].enum_values.push_back("octagramspiral");
        Options["fill_pattern"].enum_labels.push_back("rectilinear");
        Options["fill_pattern"].enum_labels.push_back("line");
        Options["fill_pattern"].enum_labels.push_back("concentric");
        Options["fill_pattern"].enum_labels.push_back("honeycomb");
        Options["fill_pattern"].enum_labels.push_back("hilbertcurve (slow)");
        Options["fill_pattern"].enum_labels.push_back("archimedeanchords (slow)");
        Options["fill_pattern"].enum_labels.push_back("octagramspiral (slow)");

        Options["first_layer_acceleration"].type = coFloat;
        Options["first_layer_acceleration"].label = "First layer";
        Options["first_layer_acceleration"].tooltip = "This is the acceleration your printer will use for first layer. Set zero to disable acceleration control for first layer.";
        Options["first_layer_acceleration"].sidetext = "mm/s²";
        Options["first_layer_acceleration"].cli = "first-layer-acceleration=f";

        Options["first_layer_bed_temperature"].type = coInt;
        Options["first_layer_bed_temperature"].label = "First layer";
        Options["first_layer_bed_temperature"].tooltip = "Heated build plate temperature for the first layer. Set this to zero to disable bed temperature control commands in the output.";
        Options["first_layer_bed_temperature"].sidetext = "°C";
        Options["first_layer_bed_temperature"].cli = "first-layer-bed-temperature=i";
        Options["first_layer_bed_temperature"].max = 300;

        Options["first_layer_extrusion_width"].type = coFloatOrPercent;
        Options["first_layer_extrusion_width"].label = "First layer";
        Options["first_layer_extrusion_width"].tooltip = "Set this to a non-zero value to set a manual extrusion width for first layer. You can use this to force fatter extrudates for better adhesion. If expressed as percentage (for example 120%) if will be computed over first layer height.";
        Options["first_layer_extrusion_width"].sidetext = "mm or % (leave 0 for default)";
        Options["first_layer_extrusion_width"].cli = "first-layer-extrusion-width=s";
        Options["first_layer_extrusion_width"].ratio_over = "first_layer_height";

        Options["first_layer_height"].type = coFloatOrPercent;
        Options["first_layer_height"].label = "First layer height";
        Options["first_layer_height"].category = "Layers and Perimeters";
        Options["first_layer_height"].tooltip = "When printing with very low layer heights, you might still want to print a thicker bottom layer to improve adhesion and tolerance for non perfect build plates. This can be expressed as an absolute value or as a percentage (for example: 150%) over the default layer height.";
        Options["first_layer_height"].sidetext = "mm or %";
        Options["first_layer_height"].cli = "first-layer-height=s";
        Options["first_layer_height"].ratio_over = "layer_height";

        Options["first_layer_speed"].type = coFloatOrPercent;
        Options["first_layer_speed"].label = "First layer speed";
        Options["first_layer_speed"].tooltip = "If expressed as absolute value in mm/s, this speed will be applied to all the print moves of the first layer, regardless of their type. If expressed as a percentage (for example: 40%) it will scale the default speeds.";
        Options["first_layer_speed"].sidetext = "mm/s or %";
        Options["first_layer_speed"].cli = "first-layer-speed=s";

        Options["first_layer_temperature"].type = coInts;
        Options["first_layer_temperature"].label = "First layer";
        Options["first_layer_temperature"].tooltip = "Extruder temperature for first layer. If you want to control temperature manually during print, set this to zero to disable temperature control commands in the output file.";
        Options["first_layer_temperature"].sidetext = "°C";
        Options["first_layer_temperature"].cli = "first-layer-temperature=i@";
        Options["first_layer_temperature"].max = 400;

        Options["g0"].type = coBool;
        Options["g0"].label = "Use G0 for travel moves";
        Options["g0"].tooltip = "Only enable this if your firmware supports G0 properly (thus decouples all axes using their maximum speeds instead of synchronizing them). Travel moves and retractions will be combined in single commands, speeding them print up.";
        Options["g0"].cli = "g0!";

        Options["gap_fill_speed"].type = coFloat;
        Options["gap_fill_speed"].label = "Gap fill";
        Options["gap_fill_speed"].tooltip = "Speed for filling small gaps using short zigzag moves. Keep this reasonably low to avoid too much shaking and resonance issues. Set zero to disable gaps filling.";
        Options["gap_fill_speed"].sidetext = "mm/s";
        Options["gap_fill_speed"].cli = "gap-fill-speed=f";

        Options["gcode_arcs"].type = coBool;
        Options["gcode_arcs"].label = "Use native G-code arcs";
        Options["gcode_arcs"].tooltip = "This experimental feature tries to detect arcs from segments and generates G2/G3 arc commands instead of multiple straight G1 commands.";
        Options["gcode_arcs"].cli = "gcode-arcs!";

        Options["gcode_comments"].type = coBool;
        Options["gcode_comments"].label = "Verbose G-code";
        Options["gcode_comments"].tooltip = "Enable this to get a commented G-code file, with each line explained by a descriptive text. If you print from SD card, the additional weight of the file could make your firmware slow down.";
        Options["gcode_comments"].cli = "gcode-comments!";

        Options["gcode_flavor"].type = coEnum;
        Options["gcode_flavor"].label = "G-code flavor";
        Options["gcode_flavor"].tooltip = "Some G/M-code commands, including temperature control and others, are not universal. Set this option to your printer's firmware to get a compatible output. The \"No extrusion\" flavor prevents Slic3r from exporting any extrusion value at all.";
        Options["gcode_flavor"].cli = "gcode-flavor=s";
        Options["gcode_flavor"].enum_keys_map = ConfigOptionEnum<GCodeFlavor>::get_enum_values();
        Options["gcode_flavor"].enum_values.push_back("reprap");
        Options["gcode_flavor"].enum_values.push_back("teacup");
        Options["gcode_flavor"].enum_values.push_back("makerware");
        Options["gcode_flavor"].enum_values.push_back("sailfish");
        Options["gcode_flavor"].enum_values.push_back("mach3");
        Options["gcode_flavor"].enum_values.push_back("no-extrusion");
        Options["gcode_flavor"].enum_labels.push_back("RepRap (Marlin/Sprinter/Repetier)");
        Options["gcode_flavor"].enum_labels.push_back("Teacup");
        Options["gcode_flavor"].enum_labels.push_back("MakerWare (MakerBot)");
        Options["gcode_flavor"].enum_labels.push_back("Sailfish (MakerBot)");
        Options["gcode_flavor"].enum_labels.push_back("Mach3/EMC");
        Options["gcode_flavor"].enum_labels.push_back("No extrusion");

        Options["infill_acceleration"].type = coFloat;
        Options["infill_acceleration"].label = "Infill";
        Options["infill_acceleration"].tooltip = "This is the acceleration your printer will use for infill. Set zero to disable acceleration control for infill.";
        Options["infill_acceleration"].sidetext = "mm/s²";
        Options["infill_acceleration"].cli = "infill-acceleration=f";

        Options["infill_every_layers"].type = coInt;
        Options["infill_every_layers"].label = "Combine infill every";
        Options["infill_every_layers"].category = "Infill";
        Options["infill_every_layers"].tooltip = "This feature allows to combine infill and speed up your print by extruding thicker infill layers while preserving thin perimeters, thus accuracy.";
        Options["infill_every_layers"].sidetext = "layers";
        Options["infill_every_layers"].cli = "infill-every-layers=i";
        Options["infill_every_layers"].full_label = "Combine infill every n layers";
        Options["infill_every_layers"].min = 1;

        Options["infill_extruder"].type = coInt;
        Options["infill_extruder"].label = "Infill extruder";
        Options["infill_extruder"].category = "Extruders";
        Options["infill_extruder"].tooltip = "The extruder to use when printing infill.";
        Options["infill_extruder"].cli = "infill-extruder=i";

        Options["infill_extrusion_width"].type = coFloatOrPercent;
        Options["infill_extrusion_width"].label = "Infill";
        Options["infill_extrusion_width"].category = "Extrusion Width";
        Options["infill_extrusion_width"].tooltip = "Set this to a non-zero value to set a manual extrusion width for infill. You may want to use fatter extrudates to speed up the infill and make your parts stronger. If expressed as percentage (for example 90%) if will be computed over layer height.";
        Options["infill_extrusion_width"].sidetext = "mm or % (leave 0 for default)";
        Options["infill_extrusion_width"].cli = "infill-extrusion-width=s";

        Options["infill_first"].type = coBool;
        Options["infill_first"].label = "Infill before perimeters";
        Options["infill_first"].tooltip = "This option will switch the print order of perimeters and infill, making the latter first.";
        Options["infill_first"].cli = "infill-first!";

        Options["infill_only_where_needed"].type = coBool;
        Options["infill_only_where_needed"].label = "Only infill where needed";
        Options["infill_only_where_needed"].category = "Infill";
        Options["infill_only_where_needed"].tooltip = "This option will limit infill to the areas actually needed for supporting ceilings (it will act as internal support material).";
        Options["infill_only_where_needed"].cli = "infill-only-where-needed!";

        Options["infill_speed"].type = coFloat;
        Options["infill_speed"].label = "Infill";
        Options["infill_speed"].tooltip = "Speed for printing the internal fill.";
        Options["infill_speed"].sidetext = "mm/s";
        Options["infill_speed"].cli = "infill-speed=f";
        Options["infill_speed"].aliases.push_back("print_feed_rate");
        Options["infill_speed"].aliases.push_back("infill_feed_rate");

        Options["layer_gcode"].type = coString;
        Options["layer_gcode"].label = "Layer change G-code";
        Options["layer_gcode"].tooltip = "This custom code is inserted at every layer change, right after the Z move and before the extruder moves to the first layer point. Note that you can use placeholder variables for all Slic3r settings.";
        Options["layer_gcode"].cli = "layer-gcode=s";
        Options["layer_gcode"].multiline = true;
        Options["layer_gcode"].full_width = true;
        Options["layer_gcode"].height = 50;

        Options["layer_height"].type = coFloat;
        Options["layer_height"].label = "Layer height";
        Options["layer_height"].category = "Layers and Perimeters";
        Options["layer_height"].tooltip = "This setting controls the height (and thus the total number) of the slices/layers. Thinner layers give better accuracy but take more time to print.";
        Options["layer_height"].sidetext = "mm";
        Options["layer_height"].cli = "layer-height=f";

        Options["max_fan_speed"].type = coInt;
        Options["max_fan_speed"].label = "Max";
        Options["max_fan_speed"].tooltip = "This setting represents the maximum speed of your fan.";
        Options["max_fan_speed"].sidetext = "%";
        Options["max_fan_speed"].cli = "max-fan-speed=i";
        Options["max_fan_speed"].max = 100;

        Options["min_fan_speed"].type = coInt;
        Options["min_fan_speed"].label = "Min";
        Options["min_fan_speed"].tooltip = "This setting represents the minimum PWM your fan needs to work.";
        Options["min_fan_speed"].sidetext = "%";
        Options["min_fan_speed"].cli = "min-fan-speed=i";
        Options["min_fan_speed"].max = 100;

        Options["min_print_speed"].type = coInt;
        Options["min_print_speed"].label = "Min print speed";
        Options["min_print_speed"].tooltip = "Slic3r will not scale speed down below this speed.";
        Options["min_print_speed"].sidetext = "mm/s";
        Options["min_print_speed"].cli = "min-print-speed=f";
        Options["min_print_speed"].max = 1000;

        Options["min_skirt_length"].type = coFloat;
        Options["min_skirt_length"].label = "Minimum extrusion length";
        Options["min_skirt_length"].tooltip = "Generate no less than the number of skirt loops required to consume the specified amount of filament on the bottom layer. For multi-extruder machines, this minimum applies to each extruder.";
        Options["min_skirt_length"].sidetext = "mm";
        Options["min_skirt_length"].cli = "min-skirt-length=f";
        Options["min_skirt_length"].min = 0;

        Options["notes"].type = coString;
        Options["notes"].label = "Configuration notes";
        Options["notes"].tooltip = "You can put here your personal notes. This text will be added to the G-code header comments.";
        Options["notes"].cli = "notes=s";
        Options["notes"].multiline = true;
        Options["notes"].full_width = true;
        Options["notes"].height = 130;

        Options["nozzle_diameter"].type = coFloats;
        Options["nozzle_diameter"].label = "Nozzle diameter";
        Options["nozzle_diameter"].tooltip = "This is the diameter of your extruder nozzle (for example: 0.5, 0.35 etc.)";
        Options["nozzle_diameter"].sidetext = "mm";
        Options["nozzle_diameter"].cli = "nozzle-diameter=f@";

        Options["only_retract_when_crossing_perimeters"].type = coBool;
        Options["only_retract_when_crossing_perimeters"].label = "Only retract when crossing perimeters";
        Options["only_retract_when_crossing_perimeters"].tooltip = "Disables retraction when the travel path does not exceed the upper layer's perimeters (and thus any ooze will be probably invisible).";
        Options["only_retract_when_crossing_perimeters"].cli = "only-retract-when-crossing-perimeters!";

        Options["ooze_prevention"].type = coBool;
        Options["ooze_prevention"].label = "Enable";
        Options["ooze_prevention"].tooltip = "This option will drop the temperature of the inactive extruders to prevent oozing. It will enable a tall skirt automatically and move extruders outside such skirt when changing temperatures.";
        Options["ooze_prevention"].cli = "ooze-prevention!";

        Options["output_filename_format"].type = coString;
        Options["output_filename_format"].label = "Output filename format";
        Options["output_filename_format"].tooltip = "You can use all configuration options as variables inside this template. For example: [layer_height], [fill_density] etc. You can also use [timestamp], [year], [month], [day], [hour], [minute], [second], [version], [input_filename], [input_filename_base].";
        Options["output_filename_format"].cli = "output-filename-format=s";
        Options["output_filename_format"].full_width = true;

        Options["overhangs"].type = coBool;
        Options["overhangs"].label = "Detect bridging perimeters";
        Options["overhangs"].category = "Layers and Perimeters";
        Options["overhangs"].tooltip = "Experimental option to adjust flow for overhangs (bridge flow will be used), to apply bridge speed to them and enable fan.";
        Options["overhangs"].cli = "overhangs!";

        Options["perimeter_acceleration"].type = coFloat;
        Options["perimeter_acceleration"].label = "Perimeters";
        Options["perimeter_acceleration"].tooltip = "This is the acceleration your printer will use for perimeters. A high value like 9000 usually gives good results if your hardware is up to the job. Set zero to disable acceleration control for perimeters.";
        Options["perimeter_acceleration"].sidetext = "mm/s²";
        Options["perimeter_acceleration"].cli = "perimeter-acceleration=f";

        Options["perimeter_extruder"].type = coInt;
        Options["perimeter_extruder"].label = "Perimeter extruder";
        Options["perimeter_extruder"].category = "Extruders";
        Options["perimeter_extruder"].tooltip = "The extruder to use when printing perimeters.";
        Options["perimeter_extruder"].cli = "perimeter-extruder=i";
        Options["perimeter_extruder"].aliases.push_back("perimeters_extruder");

        Options["perimeter_extrusion_width"].type = coFloatOrPercent;
        Options["perimeter_extrusion_width"].label = "Perimeters";
        Options["perimeter_extrusion_width"].category = "Extrusion Width";
        Options["perimeter_extrusion_width"].tooltip = "Set this to a non-zero value to set a manual extrusion width for perimeters. You may want to use thinner extrudates to get more accurate surfaces. If expressed as percentage (for example 90%) if will be computed over layer height.";
        Options["perimeter_extrusion_width"].sidetext = "mm or % (leave 0 for default)";
        Options["perimeter_extrusion_width"].cli = "perimeter-extrusion-width=s";
        Options["perimeter_extrusion_width"].aliases.push_back("perimeters_extrusion_width");

        Options["perimeter_speed"].type = coFloat;
        Options["perimeter_speed"].label = "Perimeters";
        Options["perimeter_speed"].tooltip = "Speed for perimeters (contours, aka vertical shells).";
        Options["perimeter_speed"].sidetext = "mm/s";
        Options["perimeter_speed"].cli = "perimeter-speed=f";
        Options["perimeter_speed"].aliases.push_back("perimeter_feed_rate");

        Options["perimeters"].type = coInt;
        Options["perimeters"].label = "Perimeters (minimum)";
        Options["perimeters"].category = "Layers and Perimeters";
        Options["perimeters"].tooltip = "This option sets the number of perimeters to generate for each layer. Note that Slic3r may increase this number automatically when it detects sloping surfaces which benefit from a higher number of perimeters if the Extra Perimeters option is enabled.";
        Options["perimeters"].cli = "perimeters=i";
        Options["perimeters"].aliases.push_back("perimeter_offsets");

        Options["post_process"].type = coStrings;
        Options["post_process"].label = "Post-processing scripts";
        Options["post_process"].tooltip = "If you want to process the output G-code through custom scripts, just list their absolute paths here. Separate multiple scripts with a semicolon. Scripts will be passed the absolute path to the G-code file as the first argument, and they can access the Slic3r config settings by reading environment variables.";
        Options["post_process"].cli = "post-process=s@";
        Options["post_process"].multiline = true;
        Options["post_process"].full_width = true;
        Options["post_process"].height = 60;

        Options["print_center"].type = coPoint;
        Options["print_center"].label = "Print center";
        Options["print_center"].tooltip = "These G-code coordinates are used to center your plater viewport.";
        Options["print_center"].sidetext = "mm";
        Options["print_center"].cli = "print-center=s";

        Options["raft_layers"].type = coInt;
        Options["raft_layers"].label = "Raft layers";
        Options["raft_layers"].category = "Support material";
        Options["raft_layers"].tooltip = "The object will be raised by this number of layers, and support material will be generated under it.";
        Options["raft_layers"].sidetext = "layers";
        Options["raft_layers"].cli = "raft-layers=i";

        Options["randomize_start"].type = coBool;
        Options["randomize_start"].label = "Randomize starting points";
        Options["randomize_start"].tooltip = "Start each layer from a different vertex to prevent plastic build-up on the same corner.";
        Options["randomize_start"].cli = "randomize-start!";

        Options["resolution"].type = coFloat;
        Options["resolution"].label = "Resolution";
        Options["resolution"].tooltip = "Minimum detail resolution, used to simplify the input file for speeding up the slicing job and reducing memory usage. High-resolution models often carry more detail than printers can render. Set to zero to disable any simplification and use full resolution from input.";
        Options["resolution"].sidetext = "mm";
        Options["resolution"].cli = "resolution=f";
        Options["resolution"].min = 0;

        Options["retract_before_travel"].type = coFloats;
        Options["retract_before_travel"].label = "Minimum travel after retraction";
        Options["retract_before_travel"].tooltip = "Retraction is not triggered when travel moves are shorter than this length.";
        Options["retract_before_travel"].sidetext = "mm";
        Options["retract_before_travel"].cli = "retract-before-travel=f@";

        Options["retract_layer_change"].type = coBools;
        Options["retract_layer_change"].label = "Retract on layer change";
        Options["retract_layer_change"].tooltip = "This flag enforces a retraction whenever a Z move is done.";
        Options["retract_layer_change"].cli = "retract-layer-change!";

        Options["retract_length"].type = coFloats;
        Options["retract_length"].label = "Length";
        Options["retract_length"].tooltip = "When retraction is triggered, filament is pulled back by the specified amount (the length is measured on raw filament, before it enters the extruder).";
        Options["retract_length"].sidetext = "mm (zero to disable)";
        Options["retract_length"].cli = "retract-length=f@";

        Options["retract_length_toolchange"].type = coFloats;
        Options["retract_length_toolchange"].label = "Length";
        Options["retract_length_toolchange"].tooltip = "When retraction is triggered before changing tool, filament is pulled back by the specified amount (the length is measured on raw filament, before it enters the extruder).";
        Options["retract_length_toolchange"].sidetext = "mm (zero to disable)";
        Options["retract_length_toolchange"].cli = "retract-length-toolchange=f@";

        Options["retract_lift"].type = coFloats;
        Options["retract_lift"].label = "Lift Z";
        Options["retract_lift"].tooltip = "If you set this to a positive value, Z is quickly raised every time a retraction is triggered. When using multiple extruders, only the setting for the first extruder will be considered.";
        Options["retract_lift"].sidetext = "mm";
        Options["retract_lift"].cli = "retract-lift=f@";

        Options["retract_restart_extra"].type = coFloats;
        Options["retract_restart_extra"].label = "Extra length on restart";
        Options["retract_restart_extra"].tooltip = "When the retraction is compensated after the travel move, the extruder will push this additional amount of filament. This setting is rarely needed.";
        Options["retract_restart_extra"].sidetext = "mm";
        Options["retract_restart_extra"].cli = "retract-restart-extra=f@";

        Options["retract_restart_extra_toolchange"].type = coFloats;
        Options["retract_restart_extra_toolchange"].label = "Extra length on restart";
        Options["retract_restart_extra_toolchange"].tooltip = "When the retraction is compensated after changing tool, the extruder will push this additional amount of filament.";
        Options["retract_restart_extra_toolchange"].sidetext = "mm";
        Options["retract_restart_extra_toolchange"].cli = "retract-restart-extra-toolchange=f@";

        Options["retract_speed"].type = coInts;
        Options["retract_speed"].label = "Speed";
        Options["retract_speed"].tooltip = "The speed for retractions (it only applies to the extruder motor).";
        Options["retract_speed"].sidetext = "mm/s";
        Options["retract_speed"].cli = "retract-speed=f@";
        Options["retract_speed"].max = 1000;

        Options["skirt_distance"].type = coFloat;
        Options["skirt_distance"].label = "Distance from object";
        Options["skirt_distance"].tooltip = "Distance between skirt and object(s). Set this to zero to attach the skirt to the object(s) and get a brim for better adhesion.";
        Options["skirt_distance"].sidetext = "mm";
        Options["skirt_distance"].cli = "skirt-distance=f";

        Options["skirt_height"].type = coInt;
        Options["skirt_height"].label = "Skirt height";
        Options["skirt_height"].tooltip = "Height of skirt expressed in layers. Set this to a tall value to use skirt as a shield against drafts.";
        Options["skirt_height"].sidetext = "layers";
        Options["skirt_height"].cli = "skirt-height=i";

        Options["skirts"].type = coInt;
        Options["skirts"].label = "Loops";
        Options["skirts"].tooltip = "Number of loops for this skirt, in other words its thickness. Set this to zero to disable skirt.";
        Options["skirts"].cli = "skirts=i";

        Options["slowdown_below_layer_time"].type = coInt;
        Options["slowdown_below_layer_time"].label = "Slow down if layer print time is below";
        Options["slowdown_below_layer_time"].tooltip = "If layer print time is estimated below this number of seconds, print moves speed will be scaled down to extend duration to this value.";
        Options["slowdown_below_layer_time"].sidetext = "approximate seconds";
        Options["slowdown_below_layer_time"].cli = "slowdown-below-layer-time=i";
        Options["slowdown_below_layer_time"].width = 60;
        Options["slowdown_below_layer_time"].max = 1000;

        Options["small_perimeter_speed"].type = coFloatOrPercent;
        Options["small_perimeter_speed"].label = "Small perimeters";
        Options["small_perimeter_speed"].tooltip = "This separate setting will affect the speed of perimeters having radius <= 6.5mm (usually holes). If expressed as percentage (for example: 80%) it will be calculated on the perimeters speed setting above.";
        Options["small_perimeter_speed"].sidetext = "mm/s or %";
        Options["small_perimeter_speed"].cli = "small-perimeter-speed=s";
        Options["small_perimeter_speed"].ratio_over = "perimeter_speed";

        Options["solid_fill_pattern"].type = coEnum;
        Options["solid_fill_pattern"].label = "Top/bottom fill pattern";
        Options["solid_fill_pattern"].category = "Infill";
        Options["solid_fill_pattern"].tooltip = "Fill pattern for top/bottom infill.";
        Options["solid_fill_pattern"].cli = "solid-fill-pattern=s";
        Options["solid_fill_pattern"].enum_keys_map = ConfigOptionEnum<InfillPattern>::get_enum_values();
        Options["solid_fill_pattern"].enum_values.push_back("rectilinear");
        Options["solid_fill_pattern"].enum_values.push_back("concentric");
        Options["solid_fill_pattern"].enum_values.push_back("hilbertcurve");
        Options["solid_fill_pattern"].enum_values.push_back("archimedeanchords");
        Options["solid_fill_pattern"].enum_values.push_back("octagramspiral");
        Options["solid_fill_pattern"].enum_labels.push_back("rectilinear");
        Options["solid_fill_pattern"].enum_labels.push_back("concentric");
        Options["solid_fill_pattern"].enum_labels.push_back("hilbertcurve (slow)");
        Options["solid_fill_pattern"].enum_labels.push_back("archimedeanchords (slow)");
        Options["solid_fill_pattern"].enum_labels.push_back("octagramspiral (slow)");

        Options["solid_infill_below_area"].type = coFloat;
        Options["solid_infill_below_area"].label = "Solid infill threshold area";
        Options["solid_infill_below_area"].category = "Infill";
        Options["solid_infill_below_area"].tooltip = "Force solid infill for regions having a smaller area than the specified threshold.";
        Options["solid_infill_below_area"].sidetext = "mm²";
        Options["solid_infill_below_area"].cli = "solid-infill-below-area=f";

        Options["solid_infill_every_layers"].type = coInt;
        Options["solid_infill_every_layers"].label = "Solid infill every";
        Options["solid_infill_every_layers"].category = "Infill";
        Options["solid_infill_every_layers"].tooltip = "This feature allows to force a solid layer every given number of layers. Zero to disable.";
        Options["solid_infill_every_layers"].sidetext = "layers";
        Options["solid_infill_every_layers"].cli = "solid-infill-every-layers=i";
        Options["solid_infill_every_layers"].min = 0;

        Options["solid_infill_extrusion_width"].type = coFloatOrPercent;
        Options["solid_infill_extrusion_width"].label = "Solid infill";
        Options["solid_infill_extrusion_width"].category = "Extrusion Width";
        Options["solid_infill_extrusion_width"].tooltip = "Set this to a non-zero value to set a manual extrusion width for infill for solid surfaces. If expressed as percentage (for example 90%) if will be computed over layer height.";
        Options["solid_infill_extrusion_width"].sidetext = "mm or % (leave 0 for default)";
        Options["solid_infill_extrusion_width"].cli = "solid-infill-extrusion-width=s";

        Options["solid_infill_speed"].type = coFloatOrPercent;
        Options["solid_infill_speed"].label = "Solid infill";
        Options["solid_infill_speed"].tooltip = "Speed for printing solid regions (top/bottom/internal horizontal shells). This can be expressed as a percentage (for example: 80%) over the default infill speed above.";
        Options["solid_infill_speed"].sidetext = "mm/s or %";
        Options["solid_infill_speed"].cli = "solid-infill-speed=s";
        Options["solid_infill_speed"].ratio_over = "infill_speed";
        Options["solid_infill_speed"].aliases.push_back("solid_infill_feed_rate");

        Options["solid_layers"].type = coInt;
        Options["solid_layers"].label = "Solid layers";
        Options["solid_layers"].tooltip = "Number of solid layers to generate on top and bottom surfaces.";
        Options["solid_layers"].cli = "solid-layers=i";
        Options["solid_layers"].shortcut.push_back("top_solid_layers");
        Options["solid_layers"].shortcut.push_back("bottom_solid_layers");

        Options["spiral_vase"].type = coBool;
        Options["spiral_vase"].label = "Spiral vase";
        Options["spiral_vase"].tooltip = "This experimental feature will raise Z gradually while printing a single-walled object in order to remove any visible seam. By enabling this option other settings will be overridden to enforce a single perimeter, no infill, no top solid layers, no support material. You can still set any number of bottom solid layers as well as skirt/brim loops. It won't work when printing more than an object.";
        Options["spiral_vase"].cli = "spiral-vase!";

        Options["standby_temperature_delta"].type = coInt;
        Options["standby_temperature_delta"].label = "Temperature variation";
        Options["standby_temperature_delta"].tooltip = "Temperature difference to be applied when an extruder is not active.";
        Options["standby_temperature_delta"].sidetext = "∆°C";
        Options["standby_temperature_delta"].cli = "standby-temperature-delta=i";
        Options["standby_temperature_delta"].min = -400;
        Options["standby_temperature_delta"].max = 400;

        Options["start_gcode"].type = coString;
        Options["start_gcode"].label = "Start G-code";
        Options["start_gcode"].tooltip = "This start procedure is inserted at the beginning of the output file, right after the temperature control commands for extruder and bed. If Slic3r detects M104 or M190 in your custom codes, such commands will not be prepended automatically. Note that you can use placeholder variables for all Slic3r settings, so you can put a \"M104 S[first_layer_temperature]\" command wherever you want.";
        Options["start_gcode"].cli = "start-gcode=s";
        Options["start_gcode"].multiline = true;
        Options["start_gcode"].full_width = true;
        Options["start_gcode"].height = 120;

        Options["start_perimeters_at_concave_points"].type = coBool;
        Options["start_perimeters_at_concave_points"].label = "Concave points";
        Options["start_perimeters_at_concave_points"].tooltip = "Prefer to start perimeters at a concave point.";
        Options["start_perimeters_at_concave_points"].cli = "start-perimeters-at-concave-points!";

        Options["start_perimeters_at_non_overhang"].type = coBool;
        Options["start_perimeters_at_non_overhang"].label = "Non-overhang points";
        Options["start_perimeters_at_non_overhang"].tooltip = "Prefer to start perimeters at non-overhanging points.";
        Options["start_perimeters_at_non_overhang"].cli = "start-perimeters-at-non-overhang!";

        Options["support_material"].type = coBool;
        Options["support_material"].label = "Generate support material";
        Options["support_material"].category = "Support material";
        Options["support_material"].tooltip = "Enable support material generation.";
        Options["support_material"].cli = "support-material!";

        Options["support_material_angle"].type = coInt;
        Options["support_material_angle"].label = "Pattern angle";
        Options["support_material_angle"].category = "Support material";
        Options["support_material_angle"].tooltip = "Use this setting to rotate the support material pattern on the horizontal plane.";
        Options["support_material_angle"].sidetext = "°";
        Options["support_material_angle"].cli = "support-material-angle=i";

        Options["support_material_enforce_layers"].type = coInt;
        Options["support_material_enforce_layers"].label = "Enforce support for the first";
        Options["support_material_enforce_layers"].category = "Support material";
        Options["support_material_enforce_layers"].tooltip = "Generate support material for the specified number of layers counting from bottom, regardless of whether normal support material is enabled or not and regardless of any angle threshold. This is useful for getting more adhesion of objects having a very thin or poor footprint on the build plate.";
        Options["support_material_enforce_layers"].sidetext = "layers";
        Options["support_material_enforce_layers"].cli = "support-material-enforce-layers=f";
        Options["support_material_enforce_layers"].full_label = "Enforce support for the first n layers";

        Options["support_material_extruder"].type = coInt;
        Options["support_material_extruder"].label = "Support material extruder";
        Options["support_material_extruder"].category = "Extruders";
        Options["support_material_extruder"].tooltip = "The extruder to use when printing support material. This affects brim and raft too.";
        Options["support_material_extruder"].cli = "support-material-extruder=i";

        Options["support_material_extrusion_width"].type = coFloatOrPercent;
        Options["support_material_extrusion_width"].label = "Support material";
        Options["support_material_extrusion_width"].category = "Extrusion Width";
        Options["support_material_extrusion_width"].tooltip = "Set this to a non-zero value to set a manual extrusion width for support material. If expressed as percentage (for example 90%) if will be computed over layer height.";
        Options["support_material_extrusion_width"].sidetext = "mm or % (leave 0 for default)";
        Options["support_material_extrusion_width"].cli = "support-material-extrusion-width=s";

        Options["support_material_interface_extruder"].type = coInt;
        Options["support_material_interface_extruder"].label = "Support material interface extruder";
        Options["support_material_interface_extruder"].category = "Extruders";
        Options["support_material_interface_extruder"].tooltip = "The extruder to use when printing support material interface. This affects raft too.";
        Options["support_material_interface_extruder"].cli = "support-material-interface-extruder=i";

        Options["support_material_interface_layers"].type = coInt;
        Options["support_material_interface_layers"].label = "Interface layers";
        Options["support_material_interface_layers"].category = "Support material";
        Options["support_material_interface_layers"].tooltip = "Number of interface layers to insert between the object(s) and support material.";
        Options["support_material_interface_layers"].sidetext = "layers";
        Options["support_material_interface_layers"].cli = "support-material-interface-layers=i";

        Options["support_material_interface_spacing"].type = coFloat;
        Options["support_material_interface_spacing"].label = "Interface pattern spacing";
        Options["support_material_interface_spacing"].category = "Support material";
        Options["support_material_interface_spacing"].tooltip = "Spacing between interface lines. Set zero to get a solid interface.";
        Options["support_material_interface_spacing"].sidetext = "mm";
        Options["support_material_interface_spacing"].cli = "support-material-interface-spacing=f";

        Options["support_material_pattern"].type = coEnum;
        Options["support_material_pattern"].label = "Pattern";
        Options["support_material_pattern"].category = "Support material";
        Options["support_material_pattern"].tooltip = "Pattern used to generate support material.";
        Options["support_material_pattern"].cli = "support-material-pattern=s";
        Options["support_material_pattern"].enum_keys_map = ConfigOptionEnum<SupportMaterialPattern>::get_enum_values();
        Options["support_material_pattern"].enum_values.push_back("rectilinear");
        Options["support_material_pattern"].enum_values.push_back("rectilinear-grid");
        Options["support_material_pattern"].enum_values.push_back("honeycomb");
        Options["support_material_pattern"].enum_values.push_back("pillars");
        Options["support_material_pattern"].enum_labels.push_back("rectilinear");
        Options["support_material_pattern"].enum_labels.push_back("rectilinear grid");
        Options["support_material_pattern"].enum_labels.push_back("honeycomb");
        Options["support_material_pattern"].enum_labels.push_back("pillars");

        Options["support_material_spacing"].type = coFloat;
        Options["support_material_spacing"].label = "Pattern spacing";
        Options["support_material_spacing"].category = "Support material";
        Options["support_material_spacing"].tooltip = "Spacing between support material lines.";
        Options["support_material_spacing"].sidetext = "mm";
        Options["support_material_spacing"].cli = "support-material-spacing=f";

        Options["support_material_speed"].type = coFloat;
        Options["support_material_speed"].label = "Support material";
        Options["support_material_speed"].category = "Support material";
        Options["support_material_speed"].tooltip = "Speed for printing support material.";
        Options["support_material_speed"].sidetext = "mm/s";
        Options["support_material_speed"].cli = "support-material-speed=f";

        Options["support_material_threshold"].type = coInt;
        Options["support_material_threshold"].label = "Overhang threshold";
        Options["support_material_threshold"].category = "Support material";
        Options["support_material_threshold"].tooltip = "Support material will not be generated for overhangs whose slope angle (90° = vertical) is above the given threshold. In other words, this value represent the most horizontal slope (measured from the horizontal plane) that you can print without support material. Set to zero for automatic detection (recommended).";
        Options["support_material_threshold"].sidetext = "°";
        Options["support_material_threshold"].cli = "support-material-threshold=i";

        Options["temperature"].type = coInts;
        Options["temperature"].label = "Other layers";
        Options["temperature"].tooltip = "Extruder temperature for layers after the first one. Set this to zero to disable temperature control commands in the output.";
        Options["temperature"].sidetext = "°C";
        Options["temperature"].cli = "temperature=i@";
        Options["temperature"].full_label = "Temperature";
        Options["temperature"].max = 400;

        Options["thin_walls"].type = coBool;
        Options["thin_walls"].label = "Detect thin walls";
        Options["thin_walls"].category = "Layers and Perimeters";
        Options["thin_walls"].tooltip = "Detect single-width walls (parts where two extrusions don't fit and we need to collapse them into a single trace).";
        Options["thin_walls"].cli = "thin-walls!";

        Options["threads"].type = coInt;
        Options["threads"].label = "Threads";
        Options["threads"].tooltip = "Threads are used to parallelize long-running tasks. Optimal threads number is slightly above the number of available cores/processors. Beware that more threads consume more memory.";
        Options["threads"].sidetext = "(more speed but more memory usage)";
        Options["threads"].cli = "threads|j=i";
        Options["threads"].readonly = true;
        Options["threads"].min = 1;
        Options["threads"].max = 16;

        Options["toolchange_gcode"].type = coString;
        Options["toolchange_gcode"].label = "Tool change G-code";
        Options["toolchange_gcode"].tooltip = "This custom code is inserted at every extruder change. Note that you can use placeholder variables for all Slic3r settings as well as [previous_extruder] and [next_extruder].";
        Options["toolchange_gcode"].cli = "toolchange-gcode=s";
        Options["toolchange_gcode"].multiline = true;
        Options["toolchange_gcode"].full_width = true;
        Options["toolchange_gcode"].height = 50;

        Options["top_infill_extrusion_width"].type = coFloatOrPercent;
        Options["top_infill_extrusion_width"].label = "Top solid infill";
        Options["top_infill_extrusion_width"].category = "Extrusion Width";
        Options["top_infill_extrusion_width"].tooltip = "Set this to a non-zero value to set a manual extrusion width for infill for top surfaces. You may want to use thinner extrudates to fill all narrow regions and get a smoother finish. If expressed as percentage (for example 90%) if will be computed over layer height.";
        Options["top_infill_extrusion_width"].sidetext = "mm or % (leave 0 for default)";
        Options["top_infill_extrusion_width"].cli = "top-infill-extrusion-width=s";

        Options["top_solid_infill_speed"].type = coFloatOrPercent;
        Options["top_solid_infill_speed"].label = "Top solid infill";
        Options["top_solid_infill_speed"].tooltip = "Speed for printing top solid regions. You may want to slow down this to get a nicer surface finish. This can be expressed as a percentage (for example: 80%) over the solid infill speed above.";
        Options["top_solid_infill_speed"].sidetext = "mm/s or %";
        Options["top_solid_infill_speed"].cli = "top-solid-infill-speed=s";
        Options["top_solid_infill_speed"].ratio_over = "solid_infill_speed";

        Options["top_solid_layers"].type = coInt;
        Options["top_solid_layers"].label = "Top";
        Options["top_solid_layers"].category = "Layers and Perimeters";
        Options["top_solid_layers"].tooltip = "Number of solid layers to generate on top surfaces.";
        Options["top_solid_layers"].cli = "top-solid-layers=i";
        Options["top_solid_layers"].full_label = "Top solid layers";

        Options["travel_speed"].type = coFloat;
        Options["travel_speed"].label = "Travel";
        Options["travel_speed"].tooltip = "Speed for travel moves (jumps between distant extrusion points).";
        Options["travel_speed"].sidetext = "mm/s";
        Options["travel_speed"].cli = "travel-speed=f";
        Options["travel_speed"].aliases.push_back("travel_feed_rate");

        Options["use_firmware_retraction"].type = coBool;
        Options["use_firmware_retraction"].label = "Use firmware retraction";
        Options["use_firmware_retraction"].tooltip = "This experimental setting uses G10 and G11 commands to have the firmware handle the retraction. This is only supported in recent Marlin.";
        Options["use_firmware_retraction"].cli = "use-firmware-retraction!";

        Options["use_relative_e_distances"].type = coBool;
        Options["use_relative_e_distances"].label = "Use relative E distances";
        Options["use_relative_e_distances"].tooltip = "If your firmware requires relative E values, check this, otherwise leave it unchecked. Most firmwares use absolute values.";
        Options["use_relative_e_distances"].cli = "use-relative-e-distances!";

        Options["vibration_limit"].type = coFloat;
        Options["vibration_limit"].label = "Vibration limit";
        Options["vibration_limit"].tooltip = "This experimental option will slow down those moves hitting the configured frequency limit. The purpose of limiting vibrations is to avoid mechanical resonance. Set zero to disable.";
        Options["vibration_limit"].sidetext = "Hz";
        Options["vibration_limit"].cli = "vibration-limit=f";

        Options["wipe"].type = coBools;
        Options["wipe"].label = "Wipe while retracting";
        Options["wipe"].tooltip = "This flag will move the nozzle while retracting to minimize the possible blob on leaky extruders.";
        Options["wipe"].cli = "wipe!";

        Options["z_offset"].type = coFloat;
        Options["z_offset"].label = "Z offset";
        Options["z_offset"].tooltip = "This value will be added (or subtracted) from all the Z coordinates in the output G-code. It is used to compensate for bad Z endstop position: for example, if your endstop zero actually leaves the nozzle 0.3mm far from the print bed, set this to -0.3 (or fix your endstop).";
        Options["z_offset"].sidetext = "mm";
        Options["z_offset"].cli = "z-offset=f";
        
        return Options;
    };
};

class PrintObjectConfig : public virtual StaticConfig
{
    public:
    ConfigOptionFloatOrPercent      extrusion_width;
    ConfigOptionFloatOrPercent      first_layer_height;
    ConfigOptionBool                infill_only_where_needed;
    ConfigOptionFloat               layer_height;
    ConfigOptionInt                 raft_layers;
    ConfigOptionBool                support_material;
    ConfigOptionInt                 support_material_angle;
    ConfigOptionInt                 support_material_enforce_layers;
    ConfigOptionInt                 support_material_extruder;
    ConfigOptionFloatOrPercent      support_material_extrusion_width;
    ConfigOptionInt                 support_material_interface_extruder;
    ConfigOptionInt                 support_material_interface_layers;
    ConfigOptionFloat               support_material_interface_spacing;
    ConfigOptionEnum<SupportMaterialPattern> support_material_pattern;
    ConfigOptionFloat               support_material_spacing;
    ConfigOptionFloat               support_material_speed;
    ConfigOptionInt                 support_material_threshold;
    
    PrintObjectConfig() {
        this->def = &PrintConfigDef::def;
        
        this->extrusion_width.value                              = 0;
        this->extrusion_width.percent                            = false;
        this->first_layer_height.value                           = 0.35;
        this->first_layer_height.percent                         = false;
        this->infill_only_where_needed.value                     = false;
        this->layer_height.value                                 = 0.4;
        this->raft_layers.value                                  = 0;
        this->support_material.value                             = false;
        this->support_material_angle.value                       = 0;
        this->support_material_enforce_layers.value              = 0;
        this->support_material_extruder.value                    = 1;
        this->support_material_extrusion_width.value             = 0;
        this->support_material_extrusion_width.percent           = false;
        this->support_material_interface_extruder.value          = 1;
        this->support_material_interface_layers.value            = 3;
        this->support_material_interface_spacing.value           = 0;
        this->support_material_pattern.value                     = smpHoneycomb;
        this->support_material_spacing.value                     = 2.5;
        this->support_material_speed.value                       = 60;
        this->support_material_threshold.value                   = 0;
    };
    
    ConfigOption* option(const t_config_option_key opt_key, bool create = false) {
        if (opt_key == "extrusion_width")                            return &this->extrusion_width;
        if (opt_key == "first_layer_height")                         return &this->first_layer_height;
        if (opt_key == "infill_only_where_needed")                   return &this->infill_only_where_needed;
        if (opt_key == "layer_height")                               return &this->layer_height;
        if (opt_key == "raft_layers")                                return &this->raft_layers;
        if (opt_key == "support_material")                           return &this->support_material;
        if (opt_key == "support_material_angle")                     return &this->support_material_angle;
        if (opt_key == "support_material_enforce_layers")            return &this->support_material_enforce_layers;
        if (opt_key == "support_material_extruder")                  return &this->support_material_extruder;
        if (opt_key == "support_material_extrusion_width")           return &this->support_material_extrusion_width;
        if (opt_key == "support_material_interface_extruder")        return &this->support_material_interface_extruder;
        if (opt_key == "support_material_interface_layers")          return &this->support_material_interface_layers;
        if (opt_key == "support_material_interface_spacing")         return &this->support_material_interface_spacing;
        if (opt_key == "support_material_pattern")                   return &this->support_material_pattern;
        if (opt_key == "support_material_spacing")                   return &this->support_material_spacing;
        if (opt_key == "support_material_speed")                     return &this->support_material_speed;
        if (opt_key == "support_material_threshold")                 return &this->support_material_threshold;
        
        return NULL;
    };
};

class PrintRegionConfig : public virtual StaticConfig
{
    public:
    ConfigOptionInt                 bottom_solid_layers;
    ConfigOptionBool                extra_perimeters;
    ConfigOptionInt                 fill_angle;
    ConfigOptionFloat               fill_density;
    ConfigOptionEnum<InfillPattern> fill_pattern;
    ConfigOptionInt                 infill_extruder;
    ConfigOptionFloatOrPercent      infill_extrusion_width;
    ConfigOptionInt                 infill_every_layers;
    ConfigOptionInt                 perimeter_extruder;
    ConfigOptionFloatOrPercent      perimeter_extrusion_width;
    ConfigOptionInt                 perimeters;
    ConfigOptionEnum<InfillPattern> solid_fill_pattern;
    ConfigOptionFloat               solid_infill_below_area;
    ConfigOptionFloatOrPercent      solid_infill_extrusion_width;
    ConfigOptionInt                 solid_infill_every_layers;
    ConfigOptionBool                thin_walls;
    ConfigOptionFloatOrPercent      top_infill_extrusion_width;
    ConfigOptionInt                 top_solid_layers;
    
    PrintRegionConfig() {
        this->def = &PrintConfigDef::def;
        
        this->bottom_solid_layers.value                          = 3;
        this->extra_perimeters.value                             = true;
        this->fill_angle.value                                   = 45;
        this->fill_density.value                                 = 0.4;
        this->fill_pattern.value                                 = ipHoneycomb;
        this->infill_extruder.value                              = 1;
        this->infill_extrusion_width.value                       = 0;
        this->infill_extrusion_width.percent                     = false;
        this->infill_every_layers.value                          = 1;
        this->perimeter_extruder.value                           = 1;
        this->perimeter_extrusion_width.value                    = 0;
        this->perimeter_extrusion_width.percent                  = false;
        this->perimeters.value                                   = 3;
        this->solid_fill_pattern.value                           = ipRectilinear;
        this->solid_infill_below_area.value                      = 70;
        this->solid_infill_extrusion_width.value                 = 0;
        this->solid_infill_extrusion_width.percent               = false;
        this->solid_infill_every_layers.value                    = 0;
        this->thin_walls.value                                   = true;
        this->top_infill_extrusion_width.value                   = 0;
        this->top_infill_extrusion_width.percent                 = false;
        this->top_solid_layers.value                             = 3;
    };
    
    ConfigOption* option(const t_config_option_key opt_key, bool create = false) {
        if (opt_key == "bottom_solid_layers")                        return &this->bottom_solid_layers;
        if (opt_key == "extra_perimeters")                           return &this->extra_perimeters;
        if (opt_key == "fill_angle")                                 return &this->fill_angle;
        if (opt_key == "fill_density")                               return &this->fill_density;
        if (opt_key == "fill_pattern")                               return &this->fill_pattern;
        if (opt_key == "infill_extruder")                            return &this->infill_extruder;
        if (opt_key == "infill_extrusion_width")                     return &this->infill_extrusion_width;
        if (opt_key == "infill_every_layers")                        return &this->infill_every_layers;
        if (opt_key == "perimeter_extruder")                         return &this->perimeter_extruder;
        if (opt_key == "perimeter_extrusion_width")                  return &this->perimeter_extrusion_width;
        if (opt_key == "perimeters")                                 return &this->perimeters;
        if (opt_key == "solid_fill_pattern")                         return &this->solid_fill_pattern;
        if (opt_key == "solid_infill_below_area")                    return &this->solid_infill_below_area;
        if (opt_key == "solid_infill_extrusion_width")               return &this->solid_infill_extrusion_width;
        if (opt_key == "solid_infill_every_layers")                  return &this->solid_infill_every_layers;
        if (opt_key == "thin_walls")                                 return &this->thin_walls;
        if (opt_key == "top_infill_extrusion_width")                 return &this->top_infill_extrusion_width;
        if (opt_key == "top_solid_layers")                           return &this->top_solid_layers;
        
        return NULL;
    };
};

class PrintConfig : public virtual StaticConfig
{
    public:
    ConfigOptionBool                avoid_crossing_perimeters;
    ConfigOptionPoint               bed_size;
    ConfigOptionInt                 bed_temperature;
    ConfigOptionFloat               bridge_acceleration;
    ConfigOptionInt                 bridge_fan_speed;
    ConfigOptionFloat               bridge_flow_ratio;
    ConfigOptionFloat               bridge_speed;
    ConfigOptionFloat               brim_width;
    ConfigOptionBool                complete_objects;
    ConfigOptionBool                cooling;
    ConfigOptionFloat               default_acceleration;
    ConfigOptionInt                 disable_fan_first_layers;
    ConfigOptionFloat               duplicate_distance;
    ConfigOptionString              end_gcode;
    ConfigOptionFloatOrPercent      external_perimeter_speed;
    ConfigOptionBool                external_perimeters_first;
    ConfigOptionFloat               extruder_clearance_height;
    ConfigOptionFloat               extruder_clearance_radius;
    ConfigOptionPoints              extruder_offset;
    ConfigOptionString              extrusion_axis;
    ConfigOptionFloats              extrusion_multiplier;
    ConfigOptionBool                fan_always_on;
    ConfigOptionInt                 fan_below_layer_time;
    ConfigOptionFloats              filament_diameter;
    ConfigOptionFloat               first_layer_acceleration;
    ConfigOptionInt                 first_layer_bed_temperature;
    ConfigOptionFloatOrPercent      first_layer_extrusion_width;
    ConfigOptionFloatOrPercent      first_layer_speed;
    ConfigOptionInts                first_layer_temperature;
    ConfigOptionBool                g0;
    ConfigOptionFloat               gap_fill_speed;
    ConfigOptionBool                gcode_arcs;
    ConfigOptionBool                gcode_comments;
    ConfigOptionEnum<GCodeFlavor>   gcode_flavor;
    ConfigOptionFloat               infill_acceleration;
    ConfigOptionBool                infill_first;
    ConfigOptionFloat               infill_speed;
    ConfigOptionString              layer_gcode;
    ConfigOptionInt                 max_fan_speed;
    ConfigOptionInt                 min_fan_speed;
    ConfigOptionInt                 min_print_speed;
    ConfigOptionFloat               min_skirt_length;
    ConfigOptionString              notes;
    ConfigOptionFloats              nozzle_diameter;
    ConfigOptionBool                only_retract_when_crossing_perimeters;
    ConfigOptionBool                ooze_prevention;
    ConfigOptionString              output_filename_format;
    ConfigOptionBool                overhangs;
    ConfigOptionFloat               perimeter_acceleration;
    ConfigOptionFloat               perimeter_speed;
    ConfigOptionStrings             post_process;
    ConfigOptionPoint               print_center;
    ConfigOptionBool                randomize_start;
    ConfigOptionFloat               resolution;
    ConfigOptionFloats              retract_before_travel;
    ConfigOptionBools               retract_layer_change;
    ConfigOptionFloats              retract_length;
    ConfigOptionFloats              retract_length_toolchange;
    ConfigOptionFloats              retract_lift;
    ConfigOptionFloats              retract_restart_extra;
    ConfigOptionFloats              retract_restart_extra_toolchange;
    ConfigOptionInts                retract_speed;
    ConfigOptionFloat               skirt_distance;
    ConfigOptionInt                 skirt_height;
    ConfigOptionInt                 skirts;
    ConfigOptionInt                 slowdown_below_layer_time;
    ConfigOptionFloatOrPercent      small_perimeter_speed;
    ConfigOptionFloatOrPercent      solid_infill_speed;
    ConfigOptionBool                spiral_vase;
    ConfigOptionInt                 standby_temperature_delta;
    ConfigOptionString              start_gcode;
    ConfigOptionBool                start_perimeters_at_concave_points;
    ConfigOptionBool                start_perimeters_at_non_overhang;
    ConfigOptionInts                temperature;
    ConfigOptionInt                 threads;
    ConfigOptionString              toolchange_gcode;
    ConfigOptionFloatOrPercent      top_solid_infill_speed;
    ConfigOptionFloat               travel_speed;
    ConfigOptionBool                use_firmware_retraction;
    ConfigOptionBool                use_relative_e_distances;
    ConfigOptionFloat               vibration_limit;
    ConfigOptionBools               wipe;
    ConfigOptionFloat               z_offset;
    
    PrintConfig() {
        this->def = &PrintConfigDef::def;
        
        this->avoid_crossing_perimeters.value                    = false;
        this->bed_size.point                                     = Pointf(200,200);
        this->bed_temperature.value                              = 0;
        this->bridge_acceleration.value                          = 0;
        this->bridge_fan_speed.value                             = 100;
        this->bridge_flow_ratio.value                            = 1;
        this->bridge_speed.value                                 = 60;
        this->brim_width.value                                   = 0;
        this->complete_objects.value                             = false;
        this->cooling.value                                      = true;
        this->default_acceleration.value                         = 0;
        this->disable_fan_first_layers.value                     = 1;
        this->duplicate_distance.value                           = 6;
        this->end_gcode.value                                    = "M104 S0 ; turn off temperature\nG28 X0  ; home X axis\nM84     ; disable motors\n";
        this->external_perimeter_speed.value                     = 70;
        this->external_perimeter_speed.percent                   = true;
        this->external_perimeters_first.value                    = false;
        this->extruder_clearance_height.value                    = 20;
        this->extruder_clearance_radius.value                    = 20;
        this->extruder_offset.values.resize(1);
        this->extruder_offset.values[0]                          = Pointf(0,0);
        this->extrusion_axis.value                               = "E";
        this->extrusion_multiplier.values.resize(1);
        this->extrusion_multiplier.values[0]                     = 1;
        this->fan_always_on.value                                = false;
        this->fan_below_layer_time.value                         = 60;
        this->filament_diameter.values.resize(1);
        this->filament_diameter.values[0]                        = 3;
        this->first_layer_acceleration.value                     = 0;
        this->first_layer_bed_temperature.value                  = 0;
        this->first_layer_extrusion_width.value                  = 200;
        this->first_layer_extrusion_width.percent                = true;
        this->first_layer_speed.value                            = 30;
        this->first_layer_speed.percent                          = true;
        this->first_layer_temperature.values.resize(1);
        this->first_layer_temperature.values[0]                  = 200;
        this->g0.value                                           = false;
        this->gap_fill_speed.value                               = 20;
        this->gcode_arcs.value                                   = false;
        this->gcode_comments.value                               = false;
        this->gcode_flavor.value                                 = gcfRepRap;
        this->infill_acceleration.value                          = 0;
        this->infill_first.value                                 = false;
        this->infill_speed.value                                 = 60;
        this->layer_gcode.value                                  = "";
        this->max_fan_speed.value                                = 100;
        this->min_fan_speed.value                                = 35;
        this->min_print_speed.value                              = 10;
        this->min_skirt_length.value                             = 0;
        this->notes.value                                        = "";
        this->nozzle_diameter.values.resize(1);
        this->nozzle_diameter.values[0]                          = 0.5;
        this->only_retract_when_crossing_perimeters.value        = true;
        this->ooze_prevention.value                              = false;
        this->output_filename_format.value                       = "[input_filename_base].gcode";
        this->overhangs.value                                    = true;
        this->perimeter_acceleration.value                       = 0;
        this->perimeter_speed.value                              = 30;
        this->print_center.point                                 = Pointf(100,100);
        this->randomize_start.value                              = false;
        this->resolution.value                                   = 0;
        this->retract_before_travel.values.resize(1);
        this->retract_before_travel.values[0]                    = 2;
        this->retract_layer_change.values.resize(1);
        this->retract_layer_change.values[0]                     = true;
        this->retract_length.values.resize(1);
        this->retract_length.values[0]                           = 1;
        this->retract_length_toolchange.values.resize(1);
        this->retract_length_toolchange.values[0]                = 10;
        this->retract_lift.values.resize(1);
        this->retract_lift.values[0]                             = 0;
        this->retract_restart_extra.values.resize(1);
        this->retract_restart_extra.values[0]                    = 0;
        this->retract_restart_extra_toolchange.values.resize(1);
        this->retract_restart_extra_toolchange.values[0]         = 0;
        this->retract_speed.values.resize(1);
        this->retract_speed.values[0]                            = 30;
        this->skirt_distance.value                               = 6;
        this->skirt_height.value                                 = 1;
        this->skirts.value                                       = 1;
        this->slowdown_below_layer_time.value                    = 30;
        this->small_perimeter_speed.value                        = 30;
        this->small_perimeter_speed.percent                      = false;
        this->solid_infill_speed.value                           = 60;
        this->solid_infill_speed.percent                         = false;
        this->spiral_vase.value                                  = false;
        this->standby_temperature_delta.value                    = -5;
        this->start_gcode.value                                  = "G28 ; home all axes\nG1 Z5 F5000 ; lift nozzle\n";
        this->start_perimeters_at_concave_points.value           = false;
        this->start_perimeters_at_non_overhang.value             = false;
        this->temperature.values.resize(1);
        this->temperature.values[0]                              = 200;
        this->threads.value                                      = 2;
        this->toolchange_gcode.value                             = "";
        this->top_solid_infill_speed.value                       = 50;
        this->top_solid_infill_speed.percent                     = false;
        this->travel_speed.value                                 = 130;
        this->use_firmware_retraction.value                      = false;
        this->use_relative_e_distances.value                     = false;
        this->vibration_limit.value                              = 0;
        this->wipe.values.resize(1);
        this->wipe.values[0]                                     = false;
        this->z_offset.value                                     = 0;
    };
    
    ConfigOption* option(const t_config_option_key opt_key, bool create = false) {
        if (opt_key == "avoid_crossing_perimeters")                  return &this->avoid_crossing_perimeters;
        if (opt_key == "bed_size")                                   return &this->bed_size;
        if (opt_key == "bed_temperature")                            return &this->bed_temperature;
        if (opt_key == "bridge_acceleration")                        return &this->bridge_acceleration;
        if (opt_key == "bridge_fan_speed")                           return &this->bridge_fan_speed;
        if (opt_key == "bridge_flow_ratio")                          return &this->bridge_flow_ratio;
        if (opt_key == "bridge_speed")                               return &this->bridge_speed;
        if (opt_key == "brim_width")                                 return &this->brim_width;
        if (opt_key == "complete_objects")                           return &this->complete_objects;
        if (opt_key == "cooling")                                    return &this->cooling;
        if (opt_key == "default_acceleration")                       return &this->default_acceleration;
        if (opt_key == "disable_fan_first_layers")                   return &this->disable_fan_first_layers;
        if (opt_key == "duplicate_distance")                         return &this->duplicate_distance;
        if (opt_key == "end_gcode")                                  return &this->end_gcode;
        if (opt_key == "external_perimeter_speed")                   return &this->external_perimeter_speed;
        if (opt_key == "external_perimeters_first")                  return &this->external_perimeters_first;
        if (opt_key == "extruder_clearance_height")                  return &this->extruder_clearance_height;
        if (opt_key == "extruder_clearance_radius")                  return &this->extruder_clearance_radius;
        if (opt_key == "extruder_offset")                            return &this->extruder_offset;
        if (opt_key == "extrusion_axis")                             return &this->extrusion_axis;
        if (opt_key == "extrusion_multiplier")                       return &this->extrusion_multiplier;
        if (opt_key == "fan_always_on")                              return &this->fan_always_on;
        if (opt_key == "fan_below_layer_time")                       return &this->fan_below_layer_time;
        if (opt_key == "filament_diameter")                          return &this->filament_diameter;
        if (opt_key == "first_layer_acceleration")                   return &this->first_layer_acceleration;
        if (opt_key == "first_layer_bed_temperature")                return &this->first_layer_bed_temperature;
        if (opt_key == "first_layer_extrusion_width")                return &this->first_layer_extrusion_width;
        if (opt_key == "first_layer_speed")                          return &this->first_layer_speed;
        if (opt_key == "first_layer_temperature")                    return &this->first_layer_temperature;
        if (opt_key == "g0")                                         return &this->g0;
        if (opt_key == "gap_fill_speed")                             return &this->gap_fill_speed;
        if (opt_key == "gcode_arcs")                                 return &this->gcode_arcs;
        if (opt_key == "gcode_comments")                             return &this->gcode_comments;
        if (opt_key == "gcode_flavor")                               return &this->gcode_flavor;
        if (opt_key == "infill_acceleration")                        return &this->infill_acceleration;
        if (opt_key == "infill_first")                               return &this->infill_first;
        if (opt_key == "infill_speed")                               return &this->infill_speed;
        if (opt_key == "layer_gcode")                                return &this->layer_gcode;
        if (opt_key == "max_fan_speed")                              return &this->max_fan_speed;
        if (opt_key == "min_fan_speed")                              return &this->min_fan_speed;
        if (opt_key == "min_print_speed")                            return &this->min_print_speed;
        if (opt_key == "min_skirt_length")                           return &this->min_skirt_length;
        if (opt_key == "notes")                                      return &this->notes;
        if (opt_key == "nozzle_diameter")                            return &this->nozzle_diameter;
        if (opt_key == "only_retract_when_crossing_perimeters")      return &this->only_retract_when_crossing_perimeters;
        if (opt_key == "ooze_prevention")                            return &this->ooze_prevention;
        if (opt_key == "output_filename_format")                     return &this->output_filename_format;
        if (opt_key == "overhangs")                                  return &this->overhangs;
        if (opt_key == "perimeter_acceleration")                     return &this->perimeter_acceleration;
        if (opt_key == "perimeter_speed")                            return &this->perimeter_speed;
        if (opt_key == "post_process")                               return &this->post_process;
        if (opt_key == "print_center")                               return &this->print_center;
        if (opt_key == "randomize_start")                            return &this->randomize_start;
        if (opt_key == "resolution")                                 return &this->resolution;
        if (opt_key == "retract_before_travel")                      return &this->retract_before_travel;
        if (opt_key == "retract_layer_change")                       return &this->retract_layer_change;
        if (opt_key == "retract_length")                             return &this->retract_length;
        if (opt_key == "retract_length_toolchange")                  return &this->retract_length_toolchange;
        if (opt_key == "retract_lift")                               return &this->retract_lift;
        if (opt_key == "retract_restart_extra")                      return &this->retract_restart_extra;
        if (opt_key == "retract_restart_extra_toolchange")           return &this->retract_restart_extra_toolchange;
        if (opt_key == "retract_speed")                              return &this->retract_speed;
        if (opt_key == "skirt_distance")                             return &this->skirt_distance;
        if (opt_key == "skirt_height")                               return &this->skirt_height;
        if (opt_key == "skirts")                                     return &this->skirts;
        if (opt_key == "slowdown_below_layer_time")                  return &this->slowdown_below_layer_time;
        if (opt_key == "small_perimeter_speed")                      return &this->small_perimeter_speed;
        if (opt_key == "solid_infill_speed")                         return &this->solid_infill_speed;
        if (opt_key == "spiral_vase")                                return &this->spiral_vase;
        if (opt_key == "standby_temperature_delta")                  return &this->standby_temperature_delta;
        if (opt_key == "start_gcode")                                return &this->start_gcode;
        if (opt_key == "start_perimeters_at_concave_points")         return &this->start_perimeters_at_concave_points;
        if (opt_key == "start_perimeters_at_non_overhang")           return &this->start_perimeters_at_non_overhang;
        if (opt_key == "temperature")                                return &this->temperature;
        if (opt_key == "threads")                                    return &this->threads;
        if (opt_key == "toolchange_gcode")                           return &this->toolchange_gcode;
        if (opt_key == "top_solid_infill_speed")                     return &this->top_solid_infill_speed;
        if (opt_key == "travel_speed")                               return &this->travel_speed;
        if (opt_key == "use_firmware_retraction")                    return &this->use_firmware_retraction;
        if (opt_key == "use_relative_e_distances")                   return &this->use_relative_e_distances;
        if (opt_key == "vibration_limit")                            return &this->vibration_limit;
        if (opt_key == "wipe")                                       return &this->wipe;
        if (opt_key == "z_offset")                                   return &this->z_offset;
        
        return NULL;
    };
    
    std::string get_extrusion_axis() {
        if (this->gcode_flavor == gcfMach3) {
            return std::string("A");
        } else if (this->gcode_flavor == gcfNoExtrusion) {
            return std::string("");
        }
        return this->extrusion_axis;
    }
};

class DynamicPrintConfig : public DynamicConfig
{
    public:
    DynamicPrintConfig() {
        this->def = &PrintConfigDef::def;
    };
};

class FullPrintConfig : public PrintObjectConfig, public PrintRegionConfig, public PrintConfig {
    ConfigOption* option(const t_config_option_key opt_key, bool create = false) {
        ConfigOption* opt;
        if ((opt = PrintObjectConfig::option(opt_key, create)) != NULL) return opt;
        if ((opt = PrintRegionConfig::option(opt_key, create)) != NULL) return opt;
        if ((opt = PrintConfig::option(opt_key, create)) != NULL) return opt;
        return NULL;
    };
};

}

#endif

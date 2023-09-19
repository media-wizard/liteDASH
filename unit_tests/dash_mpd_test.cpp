#include <catch2/catch_test_macros.hpp>
#include "dash_parser.h"
#include "mpd.h"
#include "period.h"
#include "baseurl.h"
#include "metrics.h"
#include "range.h"
#include "segmentbase.h"
#include "segmentlist.h"
#include "segmenttimeline.h"
#include "timeline.h"
#include "urltype.h"
#include "segmenturl.h"
#include "adaptationset.h"
#include "segmenttemplate.h"
#include "descriptor.h"
#include "segmenttimeline.h"
#include "contentprotection.h"
#include "contentcomponent.h"
#include "representation.h"
#include "subset.h"
#include "programinformation.h"

#include <stdio.h>
#include <string.h>
#include <regex>
#include <string>

/*
 * Test parsing the MPD attributes.
 */
TEST_CASE("dash_mpdparser_mpd", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\""
      "     schemaLocation=\"TestSchemaLocation\""
      "     xmlns:xsi=\"TestNamespaceXSI\""
      "     xmlns:ext=\"TestNamespaceEXT\""
      "     id=\"testId\""
      "     type=\"static\""
      "     availabilityStartTime=\"2015-03-24T1:10:50\""
      "     availabilityEndTime=\"2015-03-24T1:10:50.123456\""
      "     mediaPresentationDuration=\"P0Y1M2DT12H10M20.5S\""
      "     minimumUpdatePeriod=\"P0Y1M2DT12H10M20.5S\""
      "     minBufferTime=\"P0Y1M2DT12H10M20.5S\""
      "     timeShiftBufferDepth=\"P0Y1M2DT12H10M20.5S\""
      "     suggestedPresentationDelay=\"P0Y1M2DT12H10M20.5S\""
      "     maxSegmentDuration=\"P0Y1M2DT12H10M20.5S\""
      "     maxSubsegmentDuration=\"P0Y1M2DT12H10M20.5S\"></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    // Checking MPD attributes
    REQUIRE(mpdTree->GetId() == "testId");
    REQUIRE(mpdTree->GetType() == "static");
    REQUIRE(mpdTree->GetAvailabilityStarttime() == "2015-03-24T1:10:50");
    REQUIRE(mpdTree->GetAvailabilityEndtime() == "2015-03-24T1:10:50.123456");
    REQUIRE(mpdTree->GetMediaPresentationDuration() == "P0Y1M2DT12H10M20.5S");
    REQUIRE(mpdTree->GetMinimumUpdatePeriod() == "P0Y1M2DT12H10M20.5S");
    REQUIRE(mpdTree->GetMinBufferTime() == "P0Y1M2DT12H10M20.5S");
    REQUIRE(mpdTree->GetTimeShiftBufferDepth() == "P0Y1M2DT12H10M20.5S");
    REQUIRE(mpdTree->GetSuggestedPresentationDelay() == "P0Y1M2DT12H10M20.5S");
    REQUIRE(mpdTree->GetMaxSegmentDuration() == "P0Y1M2DT12H10M20.5S");
    REQUIRE(mpdTree->GetMaxSubsegmentDuration() == "P0Y1M2DT12H10M20.5S");
}

/*
 * Test parsing the MPD attributes.
 *
 */
TEST_CASE("liteDASH_mpdparser_mpd", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml = 
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\""
      "     schemaLocation=\"TestSchemaLocation\""
      "     xmlns:xsi=\"TestNamespaceXSI\""
      "     xmlns:ext=\"TestNamespaceEXT\""
      "     id=\"testId\""
      "     type=\"static\""
      "     availabilityStartTime=\"2015-03-24T1:10:50\""
      "     availabilityEndTime=\"2015-03-24T1:10:50.123456\""
      "     mediaPresentationDuration=\"P0Y1M2DT12H10M20.5S\""
      "     minimumUpdatePeriod=\"P0Y1M2DT12H10M20.5S\""
      "     minBufferTime=\"P0Y1M2DT12H10M20.5S\""
      "     timeShiftBufferDepth=\"P0Y1M2DT12H10M20.5S\""
      "     suggestedPresentationDelay=\"P0Y1M2DT12H10M20.5S\""
      "     maxSegmentDuration=\"P0Y1M2DT12H10M20.5S\""
      "     maxSubsegmentDuration=\"P0Y1M2DT12H10M20.5S\"></MPD>";

    char* buffer = xml.data();
    mpdTree = dash_parser.Parse(buffer, xml.length(), "");

    REQUIRE(mpdTree != nullptr);
    REQUIRE(mpdTree->GetId() == "testId"); 
    REQUIRE(mpdTree->GetType() == "static"); 
    REQUIRE(mpdTree->GetAvailabilityStarttime() == "2015-03-24T1:10:50"); 
    REQUIRE(mpdTree->GetAvailabilityEndtime() == "2015-03-24T1:10:50.123456"); 
    REQUIRE(mpdTree->GetMediaPresentationDuration() == "P0Y1M2DT12H10M20.5S"); 
}

/*
 * Test various duration formats
 */
TEST_CASE("dash_mpdparser_various_duration_formats", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml=
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\""
      "     availabilityStartTime=\"2015-03-24T0:0:0\""
      "     mediaPresentationDuration=\"P100Y\">"
      "  <Period id=\"Period0\" start=\"PT1S\"></Period>"
      "  <Period id=\"Period1\" start=\"PT1.5S\"></Period>"
      "  <Period id=\"Period2\" start=\"PT1,7S\"></Period>"
      "  <Period id=\"Period3\" start=\"PT1M\"></Period>"
      "  <Period id=\"Period4\" start=\"PT1H\"></Period>"
      "  <Period id=\"Period5\" start=\"P1D\"></Period>"
      "  <Period id=\"Period6\" start=\"P1M\"></Period>"
      "  <Period id=\"Period7\" start=\"P1Y\"></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    
    REQUIRE(periods.size() == 8); 
    
    REQUIRE(periods[0]->GetId() == "Period0");
    REQUIRE(periods[0]->GetStart() == "PT1S");

    REQUIRE(periods[1]->GetId() == "Period1");
    REQUIRE(periods[1]->GetStart() == "PT1.5S");

    REQUIRE(periods[2]->GetId() == "Period2");
    REQUIRE(periods[2]->GetStart() == "PT1,7S");

    REQUIRE(periods[3]->GetId() == "Period3");
    REQUIRE(periods[3]->GetStart() == "PT1M");

    REQUIRE(periods[4]->GetId() == "Period4");
    REQUIRE(periods[4]->GetStart() == "PT1H");

    REQUIRE(periods[5]->GetId() == "Period5");
    REQUIRE(periods[5]->GetStart() == "P1D");

    REQUIRE(periods[6]->GetId() == "Period6");
    REQUIRE(periods[6]->GetStart() == "P1M");

    REQUIRE(periods[7]->GetId() == "Period7");
    REQUIRE(periods[7]->GetStart() == "P1Y");
}

/*
 * Test parsing the ProgramInformation attributes
 *
 */
TEST_CASE("dash_mpdparser_programInformation", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <ProgramInformation lang=\"en\""
      "                      moreInformationURL=\"TestMoreInformationUrl\">"
      "    <Title>TestTitle</Title>"
      "    <Source>TestSource</Source>"
      "    <Copyright>TestCopyright</Copyright>"
      "  </ProgramInformation> </MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    const std::vector<dash::mpd::ProgramInformation*>& programInfos = mpdTree->GetProgramInformations();
    REQUIRE(programInfos.size() == 1);

    dash::mpd::ProgramInformation* programInfo = programInfos[0];
    REQUIRE(programInfo->GetLang() == "en");
    REQUIRE(programInfo->GetMoreInformationURL() == "TestMoreInformationUrl");
    REQUIRE(programInfo->GetTitle() == "TestTitle");
    REQUIRE(programInfo->GetSource() == "TestSource");
    REQUIRE(programInfo->GetCopyright() == "TestCopyright");
}

/*
 * Test various duration formats
 */
TEST_CASE("dash_mpdparser_various_duration_formats_cpp", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\""
      "     availabilityStartTime=\"2015-03-24T0:0:0\""
      "     mediaPresentationDuration=\"P100Y\">"
      "  <Period id=\"Period0\" start=\"PT1S\"></Period>"
      "  <Period id=\"Period1\" start=\"PT1.5S\"></Period>"
      "  <Period id=\"Period2\" start=\"PT1,7S\"></Period>"
      "  <Period id=\"Period3\" start=\"PT1M\"></Period>"
      "  <Period id=\"Period4\" start=\"PT1H\"></Period>"
      "  <Period id=\"Period5\" start=\"P1D\"></Period>"
      "  <Period id=\"Period6\" start=\"P1M\"></Period>"
      "  <Period id=\"Period7\" start=\"P1Y\"></Period></MPD>";


    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    
    REQUIRE(periods.size() == 8); 
    
    REQUIRE(periods[0]->GetId() == "Period0");
    REQUIRE(periods[0]->GetStart() == "PT1S");

    REQUIRE(periods[1]->GetId() == "Period1");
    REQUIRE(periods[1]->GetStart() == "PT1.5S");

    REQUIRE(periods[2]->GetId() == "Period2");
    REQUIRE(periods[2]->GetStart() == "PT1,7S");

    REQUIRE(periods[3]->GetId() == "Period3");
    REQUIRE(periods[3]->GetStart() == "PT1M");

    REQUIRE(periods[4]->GetId() == "Period4");
    REQUIRE(periods[4]->GetStart() == "PT1H");

    REQUIRE(periods[5]->GetId() == "Period5");
    REQUIRE(periods[5]->GetStart() == "P1D");

    REQUIRE(periods[6]->GetId() == "Period6");
    REQUIRE(periods[6]->GetStart() == "P1M");

    REQUIRE(periods[7]->GetId() == "Period7");
    REQUIRE(periods[7]->GetStart() == "P1Y");
}

TEST_CASE("dash_mpdparser_get_audio_languages", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period id=\"Period0\" duration=\"P0Y0M1DT1H1M1S\">"
      "    <AdaptationSet id=\"1\" mimeType=\"audio\" lang=\"en\">"
      "      <Representation id=\"1\" bandwidth=\"250000\">"
      "      </Representation>"
      "    </AdaptationSet>"
      "    <AdaptationSet id=\"2\" mimeType=\"video/mp4\">"
      "      <Representation id=\"2\" bandwidth=\"250000\">"
      "      </Representation>"
      "    </AdaptationSet>"
      "    <AdaptationSet id=\"3\" mimeType=\"audio\" lang=\"fr\">"
      "      <Representation id=\"3\" bandwidth=\"250000\">"
      "      </Representation></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];

    std::vector<dash::mpd::AdaptationSet*> adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 3);

    REQUIRE(adaptationSets[0]->GetId() == 1);
    REQUIRE(adaptationSets[0]->GetMimeType() == "audio");
    REQUIRE(adaptationSets[0]->GetLang() == "en");
    REQUIRE(adaptationSets[0]->GetRepresentation().size() == 1);

    REQUIRE(adaptationSets[0]->GetRepresentation()[0]->GetId() == "1");
    REQUIRE(adaptationSets[0]->GetRepresentation()[0]->GetBandwidth() == 250000);

    REQUIRE(adaptationSets[1]->GetId() == 2);
    REQUIRE(adaptationSets[1]->GetMimeType() == "video/mp4");
    REQUIRE(adaptationSets[1]->GetRepresentation().size() == 1);

    REQUIRE(adaptationSets[1]->GetRepresentation()[0]->GetId() == "2");
    REQUIRE(adaptationSets[1]->GetRepresentation()[0]->GetBandwidth() == 250000);

    REQUIRE(adaptationSets[2]->GetId() == 3);
    REQUIRE(adaptationSets[2]->GetMimeType() == "audio");
    REQUIRE(adaptationSets[2]->GetLang() == "fr");
    REQUIRE(adaptationSets[2]->GetRepresentation().size() == 1);

    REQUIRE(adaptationSets[2]->GetRepresentation()[0]->GetId() == "3");
    REQUIRE(adaptationSets[2]->GetRepresentation()[0]->GetBandwidth() == 250000);
}

/*
 * Test parsing the BaseURL attributes
 *
 */
TEST_CASE("dash_mpdparser_baseURL", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
        "<?xml version=\"1.0\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
        "  <BaseURL serviceLocation=\"TestServiceLocation\""
        "     byteRange=\"TestByteRange\">TestBaseURL</BaseURL></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");
    REQUIRE(mpdTree != nullptr);

    // Getting BaseURLs
    std::vector<dash::mpd::BaseUrl*> baseURLs = mpdTree->GetBaseUrls();
    
    REQUIRE(baseURLs.size() == 1); 

    REQUIRE(baseURLs[0]->GetUrl() == "TestBaseURL");
    REQUIRE(baseURLs[0]->GetServiceLocation() == "TestServiceLocation");
    REQUIRE(baseURLs[0]->GetByteRange() == "TestByteRange");
}

/*
 * Test parsing the Location attributes
 *
 */
TEST_CASE("dash_mpdparser_location", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
        "<?xml version=\"1.0\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
        "  <Location>TestLocation</Location></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");
    
    REQUIRE(mpdTree != nullptr);

    const std::vector<std::string>& locations = mpdTree->GetLocations();
    
    REQUIRE(locations.size() == 1);
    REQUIRE(locations[0] == "TestLocation");
}

/*
 * Test parsing Metrics attributes
 *
 */
TEST_CASE("dash_mpdparser_metrics", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
        "<?xml version=\"1.0\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
        "  <Metrics metrics=\"TestMetric\"></Metrics></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");
    
    REQUIRE(mpdTree != nullptr);

    const std::vector<dash::mpd::Metrics*>& metricsList = mpdTree->GetMetrics();
    
    REQUIRE(metricsList.size() == 1);
    REQUIRE(metricsList[0]->GetMetrics() == "TestMetric");
}

/*
 * Test parsing Metrics Range attributes
 *
 */
TEST_CASE("dash_mpdparser_metrics_range", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
        "<?xml version=\"1.0\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
        "  <Metrics>"
        "    <Range starttime=\"P0Y1M2DT12H10M20.5S\""
        "           duration=\"P0Y1M2DT12H10M20.1234567S\">"
        "    </Range></Metrics></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");
    
    REQUIRE(mpdTree != nullptr);

    const std::vector<dash::mpd::Metrics*>& metrics = mpdTree->GetMetrics();
    
    REQUIRE(metrics.size() == 1);
    REQUIRE(metrics[0]->GetRanges().size() == 1);

    REQUIRE(metrics[0]->GetRanges()[0]->GetStarttime() == "P0Y1M2DT12H10M20.5S");
    REQUIRE(metrics[0]->GetRanges()[0]->GetDuration() == "P0Y1M2DT12H10M20.1234567S");
}

/*
 * Test parsing Metrics Reporting attributes
 *
 */
TEST_CASE("dash_mpdparser_metrics_reporting", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
        "<?xml version=\"1.0\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
        "  <Metrics><Reporting></Reporting></Metrics></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");
    
    REQUIRE(mpdTree != nullptr);

    const std::vector<dash::mpd::Metrics*>& metrics = mpdTree->GetMetrics();
    
    REQUIRE(metrics.size() == 1);
    REQUIRE(metrics[0]->GetReportings().size() == 1);
}

/*
 * Test parsing Period attributes
 *
 */
TEST_CASE("dash_mpdparser_period", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
        "<?xml version=\"1.0\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
        "  <Period id=\"TestId\""
        "          start=\"P0Y1M2DT12H10M20.1234567S\""
        "          duration=\"P0Y1M2DT12H10M20.7654321S\""
        "          bitstreamSwitching=\"true\"></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");
    
    REQUIRE(mpdTree != nullptr);

    const std::vector<dash::mpd::Period*>& periods = mpdTree->GetPeriods();
    
    REQUIRE(periods.size() == 1);
    REQUIRE(periods[0]->GetId() == "TestId");
}

/*
 * Test parsing Period baseURL attributes
 *
 */
TEST_CASE("dash_mpdparser_period_baseURL", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
        "<?xml version=\"1.0\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
        "  <Period>"
        "    <BaseURL serviceLocation=\"TestServiceLocation\""
        "             byteRange=\"TestByteRange\">TestBaseURL</BaseURL>"
        "  </Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");
    
    REQUIRE(mpdTree != nullptr);

    const std::vector<dash::mpd::Period*>& periods = mpdTree->GetPeriods();
    
    REQUIRE(periods.size() == 1);

    const std::vector<dash::mpd::BaseUrl*>& baseUrls = periods[0]->GetBaseURLs();

    REQUIRE(baseUrls.size() == 1);
    REQUIRE(baseUrls[0]->GetServiceLocation() == "TestServiceLocation");
    REQUIRE(baseUrls[0]->GetByteRange() == "TestByteRange");
    REQUIRE(baseUrls[0]->GetUrl() == "TestBaseURL");
}

/*
 * Test parsing Period SegmentBase attributes
 */
TEST_CASE("dash_mpdparser_period_segmentBase", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
        "<?xml version=\"1.0\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
        "  <Period>"
        "    <SegmentBase timescale=\"123456\""
        "                 presentationTimeOffset=\"123456789\""
        "                 indexRange=\"100-200\""
        "                 indexRangeExact=\"true\">"
        "    </SegmentBase></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");
    
    REQUIRE(mpdTree != nullptr);

    const std::vector<dash::mpd::Period*>& periods = mpdTree->GetPeriods();
    
    REQUIRE(periods.size() == 1);

    dash::mpd::SegmentBase* segmentBase = periods[0]->GetSegmentBase();
    
    REQUIRE(segmentBase->GetTimescale() == 123456);
    REQUIRE(segmentBase->GetPresentationTimeOffset() == 123456789);
    REQUIRE(segmentBase->GetIndexRange()  == "100-200"); 
    REQUIRE(segmentBase->HasIndexRangeExact() == true);
}

/*
 * Test parsing Period SegmentList MultipleSegmentBaseType attributes
 */
TEST_CASE("dash_mpdparser_period_segmentList_multipleSegmentBaseType", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
        "<?xml version=\"1.0\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
        "  <Period>"
        "    <SegmentList duration=\"10\""
        "                 startNumber=\"11\">"
        "    </SegmentList></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");
    
    REQUIRE(mpdTree != nullptr);

    const std::vector<dash::mpd::Period*>& periods = mpdTree->GetPeriods();
    
    REQUIRE(periods.size() == 1);

    dash::mpd::SegmentList* segmentList = periods[0]->GetSegmentList();

    REQUIRE(segmentList->GetDuration() == 10);
    REQUIRE(segmentList->GetStartNumber() == 11);
}

/*
 * Test parsing Period SegmentList MultipleSegmentBaseType SegmentBaseType
 * attributes
 */
TEST_CASE("dash_mpdparser_period_segmentList_multipleSegmentBaseType_segmentBaseType", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
        "<?xml version=\"1.0\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
        "  <Period>"
        "    <SegmentList timescale=\"10\""
        "                 duration=\"1\""
        "                 presentationTimeOffset=\"11\""
        "                 indexRange=\"20-21\""
        "                 indexRangeExact=\"false\">"
        "    </SegmentList></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");
    
    REQUIRE(mpdTree != nullptr);

    const std::vector<dash::mpd::Period*>& periods = mpdTree->GetPeriods();
    
    REQUIRE(periods.size() == 1);

    dash::mpd::SegmentList* segmentList = periods[0]->GetSegmentList();

    REQUIRE(segmentList->GetTimescale() == 10);
    REQUIRE(segmentList->GetPresentationTimeOffset() == 11);
    REQUIRE(segmentList->GetIndexRange() == "20-21");
    REQUIRE(segmentList->HasIndexRangeExact() == false);
}

/*
 * Test parsing Period SegmentList MultipleSegmentBaseType SegmentTimeline
 * attributes
 */
TEST_CASE("dash_mpdparser_period_segmentList_multipleSegmentBaseType_segmentTimeline", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period>"
      "    <SegmentList>"
      "      <SegmentTimeline>"
      "      </SegmentTimeline></SegmentList></Period></MPD>";

    auto mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    auto periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);
    
    auto segmentList = periods[0]->GetSegmentList();
    REQUIRE(segmentList != nullptr);

    auto segmentTimeline = segmentList->GetSegmentTimeline();
    REQUIRE(segmentTimeline != nullptr);
}

/*
 * Test parsing Period SegmentList MultipleSegmentBaseType SegmentTimeline S
 * attributes
 */
TEST_CASE("dash_mpdparser_period_segmentList_multipleSegmentBaseType_segmentTimeline_s", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period>"
      "    <SegmentList>"
      "      <SegmentTimeline>"
      "        <S t=\"1\" d=\"2\" r=\"3\">"
      "        </S></SegmentTimeline></SegmentList></Period></MPD>";

    auto mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    auto periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);
    
    auto segmentList = periods[0]->GetSegmentList();
    REQUIRE(segmentList != nullptr);

    auto segmentTimeline  = segmentList->GetSegmentTimeline();
    REQUIRE(segmentTimeline != nullptr);

    auto sElements = segmentTimeline->GetTimelines();
    REQUIRE(sElements.size() == 1);
    REQUIRE(sElements[0]->GetStartTime() == 1);
    REQUIRE(sElements[0]->GetDuration() == 2);
    REQUIRE(sElements[0]->GetRepeatCount() == 3);
}

/*
 * Test parsing Period SegmentList MultipleSegmentBaseType BitstreamSwitching
 * attributes
 */
TEST_CASE("dash_mpdparser_period_segmentList_multipleSegmentBaseType_bitstreamSwitching", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
        "<?xml version=\"1.0\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
        "  <Period>"
        "    <SegmentList duration=\"0\">"
        "      <BitstreamSwitching sourceURL=\"TestSourceURL\""
        "                          range=\"100-200\">"
        "      </BitstreamSwitching></SegmentList></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();

    REQUIRE(periods.size() == 1);

    dash::mpd::SegmentList* segmentList = periods[0]->GetSegmentList();
    REQUIRE(segmentList != nullptr);

    REQUIRE(segmentList->GetBitstreamSwitching()->GetSourceURL() == "TestSourceURL");
}

/*
 * Test parsing Period SegmentList SegmentURL attributes
 *
 */
TEST_CASE("dash_mpdparser_period_segmentList_segmentURL", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
        "<?xml version=\"1.0\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
        "  <Period>"
        "    <SegmentList duration=\"1\">"
        "      <SegmentURL media=\"TestMedia\""
        "                  mediaRange=\"100-200\""
        "                  index=\"TestIndex\""
        "                  indexRange=\"300-400\">"
        "      </SegmentURL></SegmentList></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();

    REQUIRE(periods.size() == 1);

    dash::mpd::SegmentList* segmentList = periods[0]->GetSegmentList();
    REQUIRE(segmentList != nullptr);

    REQUIRE(segmentList->GetSegmentURLs()[0]->GetMediaURI() == "TestMedia");
    REQUIRE(segmentList->GetSegmentURLs()[0]->GetMediaRange() == "100-200");
    REQUIRE(segmentList->GetSegmentURLs()[0]->GetIndexURI() == "TestIndex");
    REQUIRE(segmentList->GetSegmentURLs()[0]->GetIndexRange() == "300-400");
}

/*
 * Test parsing Period SegmentTemplate MultipleSegmentBaseType attributes
 *
 */
TEST_CASE("dash_mpdparser_period_segmentTemplateWithPresentationTimeOffset", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml = 
        "<?xml version=\"1.0\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
        "  <Period start=\"PT1M\" duration=\"PT40S\">"
        "    <AdaptationSet"
        "      bitstreamSwitching=\"false\""
        "      mimeType=\"video/mp4\""
        "      contentType=\"video\">"
        "      <SegmentTemplate media=\"$RepresentationID$/TestMedia-$Time$.mp4\""
        "                     index=\"$RepresentationID$/TestIndex.mp4\""
        "                     timescale=\"100\""
        "                     presentationTimeOffset=\"6000\""
        "                     initialization=\"$RepresentationID$/TestInitialization\""
        "                     bitstreamSwitching=\"true\">"
        "        <SegmentTimeline>"
        "          <S d=\"400\" r=\"9\" t=\"100\"/>"
        "        </SegmentTimeline></SegmentTemplate>"
        "      <Representation bandwidth=\"95866\" frameRate=\"90000/3600\""
        "        id=\"vrep\" /></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    auto periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];
    auto adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    auto segmentTemplate = adaptationSets[0]->GetSegmentTemplate();

    REQUIRE(segmentTemplate != nullptr);
    REQUIRE(segmentTemplate->Getmedia() == "$RepresentationID$/TestMedia-$Time$.mp4");
    REQUIRE(segmentTemplate->Getindex() == "$RepresentationID$/TestIndex.mp4");
    REQUIRE(segmentTemplate->Getinitialization() == "$RepresentationID$/TestInitialization");
    REQUIRE(segmentTemplate->Getinitialization() == "$RepresentationID$/TestInitialization");
}

/*
 * Test parsing Period SegmentTemplate MultipleSegmentBaseType SegmentBaseType
 * attributes
 */
TEST_CASE("dash_mpdparser_period_segmentTemplate_multipleSegmentBaseType", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
        "<?xml version=\"1.0\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
        "  <Period>"
        "    <SegmentTemplate duration=\"10\""
        "                     startNumber=\"11\">"
        "    </SegmentTemplate></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    auto periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];
    auto segmentTemplate = period->GetSegmentTemplate();
    REQUIRE(segmentTemplate != nullptr);

    REQUIRE(segmentTemplate->GetDuration() == 10);
    REQUIRE(segmentTemplate->GetStartNumber() == 11);
}

/*
 * Test parsing Period SegmentTemplate MultipleSegmentBaseType
 * BitstreamSwitching attributes
 */
TEST_CASE("dash_mpdparser_period_segmentTemplate_multipleSegmentBaseType_bitstreamSwitching", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
        "<?xml version=\"1.0\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
        "  <Period>"
        "    <SegmentTemplate duration=\"1\">"
        "      <BitstreamSwitching sourceURL=\"TestSourceURL\""
        "                          range=\"100-200\">"
        "      </BitstreamSwitching></SegmentTemplate></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1); 

    auto segmentTemplate = periods[0]->GetSegmentTemplate(); 
    auto bitstreamSwitching = segmentTemplate->GetBitstreamSwitching(); 

    REQUIRE(bitstreamSwitching->GetSourceURL() == "TestSourceURL");

    REQUIRE(bitstreamSwitching->GetRange() == "100-200");
}

/*
 * Test parsing Period AdaptationSet attributes
 *
 */
TEST_CASE("dash_mpdparser_period_adaptationSet_attributes", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
        "<?xml version=\"1.0\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
        "  <Period>"
        "    <AdaptationSet id=\"7\""
        "                   group=\"8\""
        "                   lang=\"en\""
        "                   contentType=\"TestContentType\""
        "                   par=\"4:3\""
        "                   minBandwidth=\"100\""
        "                   maxBandwidth=\"200\""
        "                   minWidth=\"1000\""
        "                   maxWidth=\"2000\""
        "                   minHeight=\"1100\""
        "                   maxHeight=\"2100\""
        "                   minFrameRate=\"25/123\""
        "                   maxFrameRate=\"26\""
        "                   segmentAlignment=\"false\""
        "                   subsegmentAlignment=\"false\""
        "                   subsegmentStartsWithSAP=\"6\""
        "                   bitstreamSwitching=\"false\">"
        "    </AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");
    
    REQUIRE(mpdTree != nullptr);

    auto periods = mpdTree->GetPeriods();
    
    REQUIRE(periods.size() == 1);

    auto adaptation_sets = periods[0]->GetAdaptationSets();

    REQUIRE(adaptation_sets.size() == 1);

    REQUIRE(adaptation_sets[0]->GetId() == 7);
    REQUIRE(adaptation_sets[0]->GetGroup() == 8);
    REQUIRE(adaptation_sets[0]->GetLang() == "en");
    REQUIRE(adaptation_sets[0]->GetContentType() == "TestContentType");
    REQUIRE(adaptation_sets[0]->GetPar() == "4:3");
    REQUIRE(adaptation_sets[0]->GetMinBandwidth() == 100);
    REQUIRE(adaptation_sets[0]->GetMaxBandwidth() == 200);
    REQUIRE(adaptation_sets[0]->GetMinWidth() == 1000);
    REQUIRE(adaptation_sets[0]->GetMaxWidth() == 2000);
    REQUIRE(adaptation_sets[0]->GetMinHeight() == 1100);
    REQUIRE(adaptation_sets[0]->GetMaxHeight() == 2100);
    REQUIRE(adaptation_sets[0]->GetMinFramerate() == "25/123");
    REQUIRE(adaptation_sets[0]->GetMaxFramerate() == "26");
    REQUIRE(adaptation_sets[0]->GetSegmentAligment() == false);
    REQUIRE(adaptation_sets[0]->GetSubsegmentAlignment() == false);
    REQUIRE(adaptation_sets[0]->GetSubsegmentStartsWithSAP() == 6);
    REQUIRE(adaptation_sets[0]->GetBitstreamSwitching() == false);
}

/*
 * Test parsing of Perioud using @xlink:href attribute
 */
TEST_CASE("dash_mpdparser_xlink_period", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml_frag_start =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period id=\"Period0\" duration=\"PT5S\"></Period>"
      "  <Period xlink:href=\"http://404.invalid/ERROR/XML.period\""
      "          xlink:actuate=\"onRequest\""
      "          xmlns:xlink=\"http://www.w3.org/1999/xlink\"></Period></MPD>";

    mpdTree = dash_parser.Parse(xml_frag_start.data(), xml_frag_start.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 2);

    REQUIRE(periods[0]->GetId() == "Period0");
    REQUIRE(periods[0]->GetDuration() == "PT5S");

    REQUIRE(periods[1]->GetXlinkHref() == "http://404.invalid/ERROR/XML.period");
    REQUIRE(periods[1]->GetXlinkActuate() == "onRequest");
}

/*
 * Test parsing Period AdaptationSet RepresentationBase attributes
 *
 */
TEST_CASE("dash_mpdparser_period_adaptationSet_representationBase", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period>"
      "    <AdaptationSet profiles=\"TestProfiles\""
      "                   width=\"100\""
      "                   height=\"200\""
      "                   sar=\"10:20\""
      "                   frameRate=\"30/40\""
      "                   audioSamplingRate=\"TestAudioSamplingRate\""
      "                   mimeType=\"TestMimeType\""
      "                   segmentProfiles=\"TestSegmentProfiles\""
      "                   codecs=\"TestCodecs\""
      "                   maximumSAPPeriod=\"3.4\""
      "                   startWithSAP=\"0\""
      "                   maxPlayoutRate=\"1.2\""
      "                   codingDependency=\"false\""
      "                   scanType=\"progressive\">"
      "    </AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();

    REQUIRE(periods.size() == 1); 

    dash::mpd::Period* period = periods[0];
    std::vector<dash::mpd::AdaptationSet*> adaptationSets = period->GetAdaptationSets();

    auto adaptation_sets = periods[0]->GetAdaptationSets();
    
    REQUIRE(adaptation_sets.size() == 1);

    REQUIRE(adaptation_sets[0]->GetProfiles().size() == 1);
    REQUIRE(adaptation_sets[0]->GetProfiles()[0] == "TestProfiles");
    REQUIRE(adaptation_sets[0]->GetWidth() == 100);
    REQUIRE(adaptation_sets[0]->GetHeight() == 200);
    REQUIRE(adaptation_sets[0]->GetSar() == "10:20");
    REQUIRE(adaptation_sets[0]->GetFrameRate() == "30/40");
    REQUIRE(adaptation_sets[0]->GetAudioSamplingRate() == "TestAudioSamplingRate");
    REQUIRE(adaptation_sets[0]->GetMimeType() == "TestMimeType");
    REQUIRE(adaptation_sets[0]->GetSegmentProfiles()[0] == "TestSegmentProfiles");
    REQUIRE(adaptation_sets[0]->GetCodecs()[0] == "TestCodecs");
    REQUIRE(adaptation_sets[0]->GetMaximumSAPPeriod() == 3.4);
    REQUIRE(adaptation_sets[0]->GetStartWithSAP() == 0);
    REQUIRE(adaptation_sets[0]->GetMaxPlayoutRate() == 1.2);
    REQUIRE(adaptation_sets[0]->HasCodingDependency() == false);
    REQUIRE(adaptation_sets[0]->GetScanType() == "progressive");
}

/*
 * Test parsing Period AdaptationSet RepresentationBase FramePacking attributes
 *
 */
TEST_CASE("dash_mpdparser_period_adaptationSet_representationBase_framePacking", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period>"
      "    <AdaptationSet>"
      "      <FramePacking schemeIdUri=\"TestSchemeIdUri\""
      "                    value=\"TestValue\">"
      "      </FramePacking></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);
    
    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);
    
    dash::mpd::Period* firstPeriod = periods[0];
    std::vector<dash::mpd::AdaptationSet*> adaptationSets = firstPeriod->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);
    
    dash::mpd::AdaptationSet* firstAdaptationSet = adaptationSets[0];
    std::vector<dash::mpd::Descriptor*> descriptors = firstAdaptationSet->GetRole(); 
    REQUIRE(firstAdaptationSet->GetFramePacking().size() == 1);
    REQUIRE(firstAdaptationSet->GetFramePacking()[0]->GetSchemeIdUri() == "TestSchemeIdUri");
    REQUIRE(firstAdaptationSet->GetFramePacking()[0]->GetValue() == "TestValue");
}

/*
 * Test parsing Period AdaptationSet RepresentationBase
 * AudioChannelConfiguration attributes
 */
TEST_CASE("dash_mpdparser_period_segmentTemplate_multipleSegmentBaseType_segmentTimeline_s", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period>"
      "    <SegmentTemplate>"
      "      <SegmentTimeline>"
      "        <S t=\"1\" d=\"2\" r=\"3\">"
      "        </S></SegmentTimeline></SegmentTemplate></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];

    dash::mpd::SegmentTemplate* segmentTemplate = period->GetSegmentTemplate();
    REQUIRE(segmentTemplate != nullptr);

    const dash::mpd::SegmentTimeline* segmentTimeline = segmentTemplate->GetSegmentTimeline();
    REQUIRE(segmentTimeline != nullptr);

    const auto timelines = segmentTimeline->GetTimelines();
    REQUIRE(timelines.size() == 1);

    REQUIRE(timelines[0]->GetStartTime() == 1);
    REQUIRE(timelines[0]->GetDuration() == 2);
    REQUIRE(timelines[0]->GetRepeatCount() == 3);
}

/*
 * Test parsing Period AdaptationSet RepresentationBase ContentProtection
 * attributes
 */
TEST_CASE("dash_mpdparser_period_adaptationSet_representationBase_contentProtection", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period>"
      "    <AdaptationSet>"
      "      <ContentProtection schemeIdUri=\"TestSchemeIdUri\""
      "                         value=\"TestValue\">"
      "      </ContentProtection></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    auto periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];

    auto adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    dash::mpd::AdaptationSet* adaptationSet = adaptationSets[0];

    auto contentProtections = adaptationSet->GetContentProtections();
    REQUIRE(contentProtections.size() == 1);

    REQUIRE(contentProtections[0]->GetSchemeIdUri() == "TestSchemeIdUri");
    REQUIRE(contentProtections[0]->GetValue() == "TestValue");
}

/*
 * Test parsing Period AdaptationSet RepresentationBase ContentProtection
 * with custom ContentProtection content.
 */
TEST_CASE("dash_mpdparser_period_adaptationSet_representationBase_contentProtection_with_content", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\""
      "     xmlns:customns=\"foo\">"
      "  <Period>"
      "    <AdaptationSet>"
      "      <ContentProtection schemeIdUri=\"TestSchemeIdUri\">"
      "        <customns:bar>Hello world</customns:bar>"
      "      </ContentProtection></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    auto periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];
    REQUIRE(period != nullptr);

    auto adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    dash::mpd::AdaptationSet* adaptationSet = adaptationSets[0];
    REQUIRE(adaptationSet != nullptr);

    auto contentProtections = adaptationSet->GetContentProtections(); 
    REQUIRE(contentProtections.size() == 1);

    auto contentProtection = contentProtections[0];
    REQUIRE(contentProtection != nullptr);

    REQUIRE(contentProtection->GetSchemeIdUri() == "TestSchemeIdUri");
}

/*
 * Test parsing ContentProtection element that has no value attribute
 */
TEST_CASE("dash_mpdparser_contentProtection_no_value", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     xmlns:mspr=\"urn:microsoft:playready\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
        "  <Period>"
        "    <AdaptationSet>"
        "      <ContentProtection schemeIdUri=\"urn:mpeg:dash:mp4protection:2011\" value=\"cenc\"/>"
        "      <ContentProtection xmlns:mas=\"urn:marlin:mas:1-0:services:schemas:mpd\" schemeIdUri=\"urn:uuid:5e629af5-38da-4063-8977-97ffbd9902d4\">"
        "	      <mas:MarlinContentIds>"
        "	        <mas:MarlinContentId>urn:marlin:kid:02020202020202020202020202020202</mas:MarlinContentId>"
        "       </mas:MarlinContentIds>"
        "      </ContentProtection>"
        "      <ContentProtection schemeIdUri=\"urn:uuid:9a04f079-9840-4286-ab92-e65be0885f95\" value=\"MSPR 2.0\">"
        "        <mspr:pro>dGVzdA==</mspr:pro>"
        "     </ContentProtection>"
        "    </AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];
    REQUIRE(period != nullptr);

    const std::vector<dash::mpd::AdaptationSet*>& adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    dash::mpd::AdaptationSet* adaptationSet = adaptationSets[0];
    REQUIRE(adaptationSet != nullptr);

    const auto contentProtections = adaptationSet->GetContentProtections();
    REQUIRE(contentProtections.size() == 3);

    dash::mpd::Descriptor* contentProtection = contentProtections[1];
    REQUIRE(contentProtection->GetSchemeIdUri() == "urn:uuid:5e629af5-38da-4063-8977-97ffbd9902d4");
}

/*
 * Test parsing ContentProtection element that has no value attribute
 * nor an XML encoding
 */
TEST_CASE("dash_mpdparser_period_adaptationSet_representationBase_contentProtection_XML", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period>"
      "    <AdaptationSet>"
      "      <ContentProtection schemeIdUri=\"TestSchemeIdUri\""
      "                         value=\"TestValue\">"
      "      </ContentProtection></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    auto periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];

    auto adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    dash::mpd::AdaptationSet* adaptationSet = adaptationSets[0];

    auto contentProtections = adaptationSet->GetContentProtections();
    REQUIRE(contentProtections.size() == 1);

    REQUIRE(contentProtections[0]->GetSchemeIdUri() == "TestSchemeIdUri");
    REQUIRE(contentProtections[0]->GetValue() == "TestValue");
}

/*
 * Test parsing Period AdaptationSet RepresentationBase ContentProtection
 * attributes
 */
TEST_CASE("dash_mpdparser_period_adaptationSet_representationBase_contentProtection_xml_namespaces", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\" minBufferTime=\"PT1.500S\""
      "  type=\"static\" mediaPresentationDuration=\"PT0H24M28.000S\""
      "  maxSegmentDuration=\"PT0H0M4.000S\""
      "  profiles=\"urn:mpeg:dash:profile:isoff-live:2011,http://dashif.org/guidelines/dash264\""
      "  xmlns:cenc=\"urn:mpeg:cenc:2013\" xmlns:clearkey=\"http://dashif.org/guidelines/clearKey\">"
      "  <Period>" "    <AdaptationSet>"
      "      <ContentProtection schemeIdUri=\"urn:mpeg:dash:mp4protection:2011\""
      "        value=\"cenc\" cenc:default_KID=\"33969335-53A5-4E78-BA99-9054CD1B2871\">"
      "      </ContentProtection>"
      "      <ContentProtection value=\"ClearKey1.0\""
      "        schemeIdUri=\"urn:uuid:e2719d58-a985-b3c9-781a-b030af78d30e\">"
      "        <clearkey:Laurl Lic_type=\"EME-1.0\">https://drm.test.example/AcquireLicense</clearkey:Laurl>"
      "      </ContentProtection></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];
    std::vector<dash::mpd::AdaptationSet*> adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    dash::mpd::AdaptationSet* adaptationSet = adaptationSets[0];
    std::vector<dash::mpd::ContentProtection*> contentProtections = adaptationSet->GetContentProtections();
    REQUIRE(contentProtections.size() == 2);

    REQUIRE(contentProtections[0]->GetSchemeIdUri() == "urn:mpeg:dash:mp4protection:2011");
    REQUIRE(contentProtections[1]->GetSchemeIdUri() == "urn:uuid:e2719d58-a985-b3c9-781a-b030af78d30e");
}

/*
 * Test parsing Period AdaptationSet Rating attributes
 *
 */
TEST_CASE("dash_mpdparser_period_adaptationSet_representationBase_contentProtection_Rating", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period>"
      "    <AdaptationSet>"
      "      <ContentProtection schemeIdUri=\"TestSchemeIdUri\""
      "                         value=\"TestValue\">"
      "      </ContentProtection></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    auto periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];

    auto adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    dash::mpd::AdaptationSet* adaptationSet = adaptationSets[0];

    auto contentProtections = adaptationSet->GetContentProtections();
    REQUIRE(contentProtections.size() == 1);

    REQUIRE(contentProtections[0]->GetSchemeIdUri() == "TestSchemeIdUri");
    REQUIRE(contentProtections[0]->GetValue() == "TestValue");
}

/*
 * Test parsing Period AdaptationSet Viewpoint attributes
 *
 */
TEST_CASE("dash_mpdparser_period_adaptationSet_viewpoint", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
        "<?xml version=\"1.0\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
        "  <Period>"
        "    <AdaptationSet>"
        "      <Viewpoint schemeIdUri=\"TestSchemeIdUri\""
        "                 value=\"TestValue\">"
        "      </Viewpoint></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];

    std::vector<dash::mpd::AdaptationSet*> adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    dash::mpd::AdaptationSet* adaptationSet = adaptationSets[0];

    std::vector<dash::mpd::Descriptor*> viewpoints = adaptationSet->GetViewpoint();
    REQUIRE(viewpoints.size() == 1);

    dash::mpd::Descriptor* viewpoint = viewpoints[0];

    REQUIRE(viewpoint->GetSchemeIdUri() == "TestSchemeIdUri");
    REQUIRE(viewpoint->GetValue() == "TestValue");
}

/*
 * Test parsing Period AdaptationSet ContentComponent attributes
 *
 */
TEST_CASE("dash_mpdparser_period_adaptationSet_contentComponent", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period>"
      "    <AdaptationSet>"
      "      <ContentComponent id=\"1\""
      "                        lang=\"en\""
      "                        contentType=\"TestContentType\""
      "                        par=\"10:20\">"
      "      </ContentComponent></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");
    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];
    REQUIRE(period != nullptr);

    std::vector<dash::mpd::AdaptationSet*> adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    dash::mpd::AdaptationSet* adaptationSet = adaptationSets[0];
    REQUIRE(adaptationSet != nullptr);

    std::vector<dash::mpd::ContentComponent*> contentComponents = adaptationSet->GetContentComponent();
    REQUIRE(contentComponents.size() == 1);

    dash::mpd::ContentComponent* contentComponent = contentComponents[0];
    REQUIRE(contentComponent != nullptr);
    REQUIRE(contentComponent->GetId() == 1);
    REQUIRE(contentComponent->GetLang() == "en");
    REQUIRE(contentComponent->GetContentType() == "TestContentType");
    REQUIRE(contentComponent->GetPar() == "10:20");
}

/*
 * Test parsing Period AdaptationSet ContentComponent Accessibility attributes
 *
 */
TEST_CASE("dash_mpdparser_period_adaptationSet_contentComponent_accessibility", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
        "<?xml version=\"1.0\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
        "  <Period>"
        "    <AdaptationSet>"
        "      <ContentComponent>"
        "        <Accessibility schemeIdUri=\"TestSchemeIdUri\""
        "                       value=\"TestValue\">"
        "        </Accessibility>"
        "      </ContentComponent></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];
    REQUIRE(period != nullptr);

    std::vector<dash::mpd::AdaptationSet*> adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    dash::mpd::AdaptationSet* adaptationSet = adaptationSets[0];
    REQUIRE(adaptationSet != nullptr);

    std::vector<dash::mpd::ContentComponent*> contentComponents = adaptationSet->GetContentComponent();
    REQUIRE(contentComponents.size() == 1);

    dash::mpd::ContentComponent* contentComponent = contentComponents[0];

    std::vector<dash::mpd::Descriptor*> accessibilities = contentComponent->GetAccessibility();
    REQUIRE(accessibilities.size() == 1);

    dash::mpd::Descriptor* accessibility = accessibilities[0];
    REQUIRE(accessibility->GetSchemeIdUri() == "TestSchemeIdUri");
    REQUIRE(accessibility->GetValue() == "TestValue");
}

/*
 * Test parsing Period AdaptationSet ContentComponent Role attributes
 *
 */
TEST_CASE("dash_mpdparser_period_adaptationSet_contentComponent_role", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period>"
      "    <AdaptationSet>"
      "      <ContentComponent>"
      "        <Role schemeIdUri=\"TestSchemeIdUri\""
      "              value=\"TestValue\">"
      "        </Role></ContentComponent></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];

    const std::vector<dash::mpd::AdaptationSet*>& adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    dash::mpd::AdaptationSet* adaptationSet = adaptationSets[0];

    const std::vector<dash::mpd::ContentComponent*>& contentComponents = adaptationSet->GetContentComponent();
    REQUIRE(contentComponents.size() == 1);

    const std::vector<dash::mpd::Descriptor*>& roles = contentComponents[0]->GetRole();
    REQUIRE(roles.size() == 1);

    REQUIRE(roles[0]->GetSchemeIdUri() == "TestSchemeIdUri");
    REQUIRE(roles[0]->GetValue() == "TestValue");
}

/*
 * Test parsing Period AdaptationSet ContentComponent Rating attributes
 *
 */
TEST_CASE("dash_mpdparser_period_adaptationSet_contentComponent_rating", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period>"
      "    <AdaptationSet>"
      "      <ContentComponent>"
      "        <Rating schemeIdUri=\"TestSchemeIdUri\""
      "                value=\"TestValue\">"
      "        </Rating>"
      "      </ContentComponent></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];
    REQUIRE(period != nullptr);

    const std::vector<dash::mpd::AdaptationSet*>& adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    dash::mpd::AdaptationSet* adaptationSet = adaptationSets[0];
    REQUIRE(adaptationSet != nullptr);

    const std::vector<dash::mpd::ContentComponent*>& contentComponents = adaptationSet->GetContentComponent();
    REQUIRE(contentComponents.size() == 1);

    const std::vector<dash::mpd::Descriptor*>& ratings = contentComponents[0]->GetRating();
    REQUIRE(ratings.size() == 1);

    dash::mpd::Descriptor* rating = ratings[0];
    REQUIRE(rating != nullptr);
    REQUIRE(rating->GetSchemeIdUri() == "TestSchemeIdUri");
    REQUIRE(rating->GetValue() == "TestValue");
}

/*
 * Test parsing Period AdaptationSet ContentComponent Viewpoint attributes
 *
 */
TEST_CASE("dash_mpdparser_period_adaptationSet_contentComponent_Viewpoint", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period>"
      "    <AdaptationSet>"
      "      <ContentComponent>"
      "        <Role schemeIdUri=\"TestSchemeIdUri\""
      "              value=\"TestValue\">"
      "        </Role></ContentComponent></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];

    const std::vector<dash::mpd::AdaptationSet*>& adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    dash::mpd::AdaptationSet* adaptationSet = adaptationSets[0];

    const std::vector<dash::mpd::ContentComponent*>& contentComponents = adaptationSet->GetContentComponent();
    REQUIRE(contentComponents.size() == 1);

    const std::vector<dash::mpd::Descriptor*>& roles = contentComponents[0]->GetRole();
    REQUIRE(roles.size() == 1);

    REQUIRE(roles[0]->GetSchemeIdUri() == "TestSchemeIdUri");
    REQUIRE(roles[0]->GetValue() == "TestValue");
}

/*
 * Test parsing Period AdaptationSet BaseURL attributes
 */
TEST_CASE("dash_mpdparser_period_adaptationSet_baseURL", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period>"
      "    <AdaptationSet>"
      "      <BaseURL serviceLocation=\"TestServiceLocation\""
      "               byteRange=\"TestByteRange\">TestBaseURL</BaseURL>"
      "    </AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];
    REQUIRE(period != nullptr);

    const std::vector<dash::mpd::AdaptationSet*>& adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    dash::mpd::AdaptationSet* adaptationSet = adaptationSets[0];
    REQUIRE(adaptationSet != nullptr);

    const std::vector<dash::mpd::BaseUrl*>& baseUrls = adaptationSet->GetBaseURLs();
    REQUIRE(baseUrls.size() == 1);

    dash::mpd::BaseUrl* baseUrl = baseUrls[0];
    REQUIRE(baseUrl != nullptr);

    REQUIRE(baseUrl->GetServiceLocation() == "TestServiceLocation");
    REQUIRE(baseUrl->GetByteRange() == "TestByteRange");
    REQUIRE(baseUrl->GetUrl() == "TestBaseURL");
}

/*
 * Test parsing Period AdaptationSet SegmentBase attributes
 *
 */
TEST_CASE("dash_mpdparser_period_adaptationSet_contentComponent_segmentBase", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period>"
      "    <AdaptationSet>"
      "      <ContentComponent>"
      "        <Role schemeIdUri=\"TestSchemeIdUri\""
      "              value=\"TestValue\">"
      "        </Role></ContentComponent></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];

    const std::vector<dash::mpd::AdaptationSet*>& adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    dash::mpd::AdaptationSet* adaptationSet = adaptationSets[0];

    const std::vector<dash::mpd::ContentComponent*>& contentComponents = adaptationSet->GetContentComponent();
    REQUIRE(contentComponents.size() == 1);

    const std::vector<dash::mpd::Descriptor*>& roles = contentComponents[0]->GetRole();
    REQUIRE(roles.size() == 1);

    REQUIRE(roles[0]->GetSchemeIdUri() == "TestSchemeIdUri");
    REQUIRE(roles[0]->GetValue() == "TestValue");
}

/*
 * Test parsing Period AdaptationSet SegmentBase RepresentationIndex attributes
 *
 */
TEST_CASE("dash_mpdparser_period_adaptationSet_segmentBase_representationIndex", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period>"
      "    <AdaptationSet>"
      "      <SegmentBase>"
      "        <RepresentationIndex sourceURL=\"TestSourceURL\""
      "                             range=\"100-200\">"
      "        </RepresentationIndex>"
      "      </SegmentBase></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    auto periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];
    auto adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    dash::mpd::AdaptationSet* adaptationSet = adaptationSets[0];
    auto* segmentBase = adaptationSet->GetSegmentBase();
    REQUIRE(segmentBase != nullptr);

    auto* representationIndex = segmentBase->GetRepresentationIndex();
    REQUIRE(representationIndex != nullptr);
    REQUIRE(representationIndex->GetSourceURL() == "TestSourceURL");

    std::string range = representationIndex->GetRange();
    REQUIRE(range == "100-200");
}

/*
 * Test parsing Period AdaptationSet SegmentList attributes
 *
 */
TEST_CASE("dash_mpdparser_period_adaptationSet_contentComponent_segmentList", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period>"
      "    <AdaptationSet>"
      "      <ContentComponent>"
      "        <Role schemeIdUri=\"TestSchemeIdUri\""
      "              value=\"TestValue\">"
      "        </Role></ContentComponent></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];

    const std::vector<dash::mpd::AdaptationSet*>& adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    dash::mpd::AdaptationSet* adaptationSet = adaptationSets[0];

    const std::vector<dash::mpd::ContentComponent*>& contentComponents = adaptationSet->GetContentComponent();
    REQUIRE(contentComponents.size() == 1);

    const std::vector<dash::mpd::Descriptor*>& roles = contentComponents[0]->GetRole();
    REQUIRE(roles.size() == 1);

    REQUIRE(roles[0]->GetSchemeIdUri() == "TestSchemeIdUri");
    REQUIRE(roles[0]->GetValue() == "TestValue");
}

/*
 * Test parsing Period AdaptationSet Representation attributes
 *
 */
TEST_CASE("dash_mpdparser_period_adaptationSet_representation", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period>"
      "    <AdaptationSet>"
      "      <Representation id=\"Test_Id\""
      "                      bandwidth=\"100\""
      "                      qualityRanking=\"200\""
      "                      dependencyId=\"one two three\""
      "                      mediaStreamStructureId=\"\">"
      "      </Representation></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    auto periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];
    REQUIRE(period != nullptr);

    auto adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    dash::mpd::AdaptationSet* adaptationSet = adaptationSets[0];
    REQUIRE(adaptationSet != nullptr);

    auto representations = adaptationSet->GetRepresentation();
    REQUIRE(representations.size() == 1);

    dash::mpd::Representation* representation = representations[0];
    REQUIRE(representation != nullptr);

    REQUIRE(representation->GetId() == "Test_Id");
    REQUIRE(representation->GetBandwidth() == 100);
    REQUIRE(representation->GetQualityRanking() == 200);
    REQUIRE(representation->GetDependencyId()[0] == "one two three");
}

/*
 * Test parsing Period AdaptationSet Representation RepresentationBaseType attributes
 *
 */
TEST_CASE("dash_mpdparser_period_adaptationSet_representation_representationBase", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period>"
      "    <AdaptationSet>"
      "      <Representation id=\"1\" bandwidth=\"250000\">"
      "      </Representation></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];
    REQUIRE(period != nullptr);

    std::vector<dash::mpd::AdaptationSet*> adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    dash::mpd::AdaptationSet* adaptationSet = adaptationSets[0];
    REQUIRE(adaptationSet != nullptr);

    std::vector<dash::mpd::Representation*> representations = adaptationSet->GetRepresentation();
    REQUIRE(representations.size() == 1);

    dash::mpd::Representation* representation = representations[0];
    REQUIRE(representation != nullptr);

    REQUIRE(representation->GetId() == "1");
    REQUIRE(representation->GetBandwidth() == 250000);
}

/*
 * Test parsing Period AdaptationSet Representation BaseURL attributes
 *
 */
TEST_CASE("dash_mpdparser_period_adaptationSet_representation_baseURL", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period>"
      "    <AdaptationSet>"
      "      <Representation id=\"1\" bandwidth=\"250000\">"
      "        <BaseURL serviceLocation=\"TestServiceLocation\""
      "                 byteRange=\"TestByteRange\">TestBaseURL</BaseURL>"
      "      </Representation></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");
    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];
    const std::vector<dash::mpd::AdaptationSet*>& adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    dash::mpd::AdaptationSet* adaptationSet = adaptationSets[0];
    const std::vector<dash::mpd::Representation*>& representations = adaptationSet->GetRepresentation();
    REQUIRE(representations.size() == 1);

    dash::mpd::Representation* representation = representations[0];
    const std::vector<dash::mpd::BaseUrl*>& baseUrls = representation->GetBaseURLs();
    REQUIRE(baseUrls.size() == 1);

    dash::mpd::BaseUrl* baseUrl = baseUrls[0];
    REQUIRE(baseUrl->GetUrl() == "TestBaseURL");
    REQUIRE(baseUrl->GetServiceLocation() == "TestServiceLocation");
    REQUIRE(baseUrl->GetByteRange() == "TestByteRange");
}

/*
 * Test parsing Period AdaptationSet Representation SubRepresentation attributes
 *
 */
TEST_CASE("dash_mpdparser_period_adaptationSet_representation_SubRepresentation", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period>"
      "    <AdaptationSet>"
      "      <Representation id=\"1\" bandwidth=\"250000\">"
      "      </Representation></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];
    REQUIRE(period != nullptr);

    std::vector<dash::mpd::AdaptationSet*> adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    dash::mpd::AdaptationSet* adaptationSet = adaptationSets[0];
    REQUIRE(adaptationSet != nullptr);

    std::vector<dash::mpd::Representation*> representations = adaptationSet->GetRepresentation();
    REQUIRE(representations.size() == 1);

    dash::mpd::Representation* representation = representations[0];
    REQUIRE(representation != nullptr);

    REQUIRE(representation->GetId() == "1");
    REQUIRE(representation->GetBandwidth() == 250000);
}

/*
 * Test parsing Period Subset attributes
 *
 */
TEST_CASE("dash_mpdparser_period_subset", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period><Subset contains=\"1\"></Subset></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");
    
    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];

    const auto& subsets = period->GetSubsets();
    REQUIRE(subsets.size() == 1);

    const auto& containsValues = subsets[0]->Contains();
    REQUIRE(containsValues.size() == 1);
    REQUIRE(containsValues[0] == 1);
}

/*
 * Test parsing UTCTiming elements
 *
 */
TEST_CASE("dash_mpdparser_utctiming", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      " profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "<UTCTiming schemeIdUri=\"urn:mpeg:dash:utc:http-xsdate:2014\" value=\"http://time.akamai.com/?iso http://example.time/xsdate\"/>"
      "<UTCTiming schemeIdUri=\"urn:mpeg:dash:utc:direct:2014\" value=\"2002-05-30T09:30:10Z \"/>"
      "<UTCTiming schemeIdUri=\"urn:mpeg:dash:utc:ntp:2014\" value=\"0.europe.pool.ntp.org 1.europe.pool.ntp.org 2.europe.pool.ntp.org 3.europe.pool.ntp.org\"/>"
      "</MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    auto utcTimings = mpdTree->GetUTCTimings();
    REQUIRE(utcTimings.size() == 3);

    REQUIRE(utcTimings[0]->GetSchemeIdUri() == "urn:mpeg:dash:utc:http-xsdate:2014");
    REQUIRE(utcTimings[0]->GetValue() == "http://time.akamai.com/?iso http://example.time/xsdate");
}

/*
 * Test parsing the type property: value "dynamic"
 *
 */
TEST_CASE("dash_mpdparser_type_dynamic", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD type=\"dynamic\" xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\"> </MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    const std::string& type = mpdTree->GetType();
    REQUIRE(type == "dynamic");
}

/*
 * Test handling isoff ondemand profile
 *
 */
TEST_CASE("dash_mpdparser_isoff_ondemand_profile", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-on-demand:2011\"></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    auto profiles = mpdTree->GetProfiles();
    REQUIRE(profiles.size() > 0); 

    bool hasOnDemandProfile = false;
    for (const auto& profile : profiles) {
        if (profile == "urn:mpeg:dash:profile:isoff-on-demand:2011") {
            hasOnDemandProfile = true;
            break;
        }
    }
    
    REQUIRE(hasOnDemandProfile);
}

/*
 * Test bitstreamSwitching inheritance from Period to AdaptationSet
 *
 * Description of bistreamSwitching attribute in Period:
 * "When set to ‘true’, this is equivalent as if the
 * AdaptationSet@bitstreamSwitching for each Adaptation Set contained in this
 * Period is set to 'true'. In this case, the AdaptationSet@bitstreamSwitching
 * attribute shall not be set to 'false' for any Adaptation Set in this Period"
 *
 */
TEST_CASE("dash_mpdparser_bitstreamSwitching_inheritance_from_period", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period id=\"Period0\""
      "          duration=\"P0Y0M1DT1H1M1S\""
      "          bitstreamSwitching=\"true\">"
      "    <AdaptationSet id=\"1\""
      "                   mimeType=\"video/mp4\">"
      "      <Representation id=\"1\" bandwidth=\"250000\">"
      "      </Representation>"
      "    </AdaptationSet>"
      "    <AdaptationSet id=\"2\""
      "                   mimeType=\"audio\""
      "                   bitstreamSwitching=\"false\">"
      "      <Representation id=\"2\" bandwidth=\"250000\">"
      "      </Representation></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");
    
    REQUIRE(mpdTree != nullptr);

    auto periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    auto period = periods[0];
    REQUIRE(period->GetBitstreamSwitching() == true);

    auto adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 2);
}

/*
 * Test setting a stream
 *
 */
TEST_CASE("dash_mpdparser_setup_streaming", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
        "<?xml version=\"1.0\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
        "  <Period id=\"Period0\""
        "          duration=\"P0Y0M1DT1H1M1S\">"
        "    <AdaptationSet id=\"1\""
        "                   mimeType=\"video/mp4\">"
        "      <Representation id=\"1\" bandwidth=\"250000\">"
        "      </Representation></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");
    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];

    std::vector<dash::mpd::AdaptationSet*> adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    dash::mpd::AdaptationSet* adapt_set = adaptationSets[0];
    REQUIRE(adapt_set != nullptr);

    REQUIRE(adapt_set->GetId() == 1);
}

/*
 * Test handling Period selection
 *
 */
TEST_CASE("dash_mpdparser_period_selection", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
        "<?xml version=\"1.0\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\""
        "     mediaPresentationDuration=\"P0Y0M1DT1H4M3S\">"
        "  <Period id=\"Period0\" duration=\"P0Y0M1DT1H1M1S\"></Period>"
        "  <Period id=\"Period1\"></Period>"
        "  <Period id=\"Period2\" start=\"P0Y0M1DT1H3M3S\"></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 3);

    REQUIRE(periods[0]->GetId() == "Period0");
    REQUIRE(periods[1]->GetId() == "Period1");
    REQUIRE(periods[2]->GetId() == "Period2");

    REQUIRE(mpdTree->GetPeriods()[0]->GetId() == "Period0");
    REQUIRE(mpdTree->GetPeriods()[1]->GetId() == "Period1");
    REQUIRE(mpdTree->GetPeriods()[2]->GetId() == "Period2");
}
/*
 * Test handling Adaptation sets
 *
 */
TEST_CASE("dash_mpdparser_adaptationSet_handling", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period id=\"Period0\" duration=\"P0Y0M1DT1H1M1S\">"
      "    <AdaptationSet id=\"1\"></AdaptationSet>"
      "  </Period>"
      "  <Period id=\"Period1\" duration=\"P0Y0M1DT1H1M1S\">"
      "    <AdaptationSet id=\"10\"></AdaptationSet>"
      "    <AdaptationSet id=\"11\"></AdaptationSet>"
      "  </Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 2);

    // Testing Period0
    dash::mpd::Period* period0 = periods[0];
    REQUIRE(period0->GetId() == "Period0");
    std::vector<dash::mpd::AdaptationSet*> adaptationSetsPeriod0 = period0->GetAdaptationSets();
    REQUIRE(adaptationSetsPeriod0.size() == 1);
    REQUIRE(adaptationSetsPeriod0[0]->GetId() == 1);

    // Testing Period1
    dash::mpd::Period* period1 = periods[1];
    REQUIRE(period1->GetId() == "Period1");
    std::vector<dash::mpd::AdaptationSet*> adaptationSetsPeriod1 = period1->GetAdaptationSets();
    REQUIRE(adaptationSetsPeriod1.size() == 2);
    REQUIRE(adaptationSetsPeriod1[0]->GetId() == 10);
    REQUIRE(adaptationSetsPeriod1[1]->GetId() == 11);
}

/*
 * Test handling Representation selection
 *
 */
TEST_CASE("dash_mpdparser_representation_selection", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
        "<?xml version=\"1.0\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
        "  <Period id=\"Period0\" duration=\"P0Y0M1DT1H1M1S\">"
        "    <AdaptationSet id=\"1\" mimeType=\"video/mp4\">"
        "      <Representation id=\"v0\" bandwidth=\"500000\"></Representation>"
        "      <Representation id=\"v1\" bandwidth=\"250000\"></Representation>"
        "    </AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    auto periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];

    auto adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    dash::mpd::AdaptationSet* adaptationSet = adaptationSets[0];
    REQUIRE(adaptationSet->GetId() == 1);

    auto representations = adaptationSet->GetRepresentation();
    REQUIRE(representations.size() == 2);

    REQUIRE(representations[0]->GetBandwidth() == 500000);
    REQUIRE(representations[1]->GetBandwidth() == 250000);
}

/*
 * Test getting Active stream parameters
 *
 */
TEST_CASE("dash_mpdparser_activeStream_parameters", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\">"
      "  <Period id=\"Period0\""
      "          duration=\"P0Y0M1DT1H1M1S\">"
      "    <AdaptationSet id=\"1\""
      "                   mimeType=\"video/mp4\""
      "                   width=\"320\""
      "                   height=\"240\""
      "                   bitstreamSwitching=\"true\""
      "                   audioSamplingRate=\"48000\">"
      "      <Representation id=\"1\" bandwidth=\"250000\">"
      "      </Representation></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    auto periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    auto period = periods[0];
    REQUIRE(period != nullptr);

    auto adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    auto adapt_set = adaptationSets[0];
    REQUIRE(adapt_set != nullptr);

    REQUIRE(adapt_set->GetMimeType() == "video/mp4");
    REQUIRE(adapt_set->GetWidth() == 320);
    REQUIRE(adapt_set->GetHeight() == 240);
    REQUIRE(adapt_set->GetBitstreamSwitching() == true);

    auto representations = adapt_set->GetRepresentation();
    REQUIRE(representations.size() == 1);

    auto representation = representations[0];
    REQUIRE(representation != nullptr);

    REQUIRE(representation->GetBandwidth() == 250000);
}

/*
 * Test getting mediaPresentationDuration
 *
 */
TEST_CASE("dash_mpdparser_get_mediaPresentationDuration", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\""
      "     mediaPresentationDuration=\"P0Y0M0DT0H0M3S\"></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");
    REQUIRE(mpdTree != nullptr);

    const std::string& mediaPresentationDuration = mpdTree->GetMediaPresentationDuration();
    REQUIRE(mediaPresentationDuration == "P0Y0M0DT0H0M3S");
}

/*
 * Test getting streamPresentationOffset
 *
 */
TEST_CASE("dash_mpdparser_get_streamPresentationOffset", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\""
      "     mediaPresentationDuration=\"P0Y0M0DT3H3M30S\">"
      "  <Period>"
      "    <AdaptationSet mimeType=\"video/mp4\">"
      "      <SegmentBase timescale=\"1000\" presentationTimeOffset=\"3000\">"
      "      </SegmentBase>"
      "      <Representation id=\"1\" bandwidth=\"250000\">"
      "      </Representation></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");
    REQUIRE(mpdTree != nullptr);

    auto periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    auto period = periods[0];
    REQUIRE(period != nullptr);

    auto adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    auto adapt_set = adaptationSets[0];
    REQUIRE(adapt_set != nullptr);

    auto segmentBase = adapt_set->GetSegmentBase();
    REQUIRE(segmentBase != nullptr);

    auto representations = adapt_set->GetRepresentation();
    REQUIRE(representations.size() == 1);

    auto representation = representations[0];
    REQUIRE(representation != nullptr);
    REQUIRE(representation->GetId() == "1");
    REQUIRE(representation->GetBandwidth() == 250000);
}

/*
 * Test handling segments
 *
 */

TEST_CASE("dash_mpdparser_segments", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     type=\"dynamic\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\""
      "     availabilityStartTime=\"2015-03-24T0:0:0\""
      "     mediaPresentationDuration=\"P0Y0M0DT3H3M30S\">"
      "  <Period id=\"Period0\" start=\"P0Y0M0DT0H0M10S\">"
      "    <AdaptationSet mimeType=\"video/mp4\">"
      "      <Representation id=\"1\" bandwidth=\"250000\">"
      "        <SegmentList duration=\"45\">"
      "          <SegmentURL media=\"TestMedia1\""
      "                      mediaRange=\"10-20\""
      "                      index=\"TestIndex1\""
      "                      indexRange=\"30-40\">"
      "          </SegmentURL>"
      "          <SegmentURL media=\"TestMedia2\""
      "                      mediaRange=\"20-30\""
      "                      index=\"TestIndex2\""
      "                      indexRange=\"40-50\">"
      "          </SegmentURL>"
      "        </SegmentList>"
      "      </Representation></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    dash::mpd::Period* period = periods[0];
    REQUIRE(period != nullptr);

    std::vector<dash::mpd::AdaptationSet*> adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);
    dash::mpd::AdaptationSet* adaptationSet = adaptationSets[0];
    REQUIRE(adaptationSet != nullptr);
    
    auto representation = adaptationSets[0]->GetRepresentation();
    auto* segmentList = representation[0]->GetSegmentList(); 
    
    REQUIRE(segmentList != nullptr);
    auto segmentUTL = segmentList->GetSegmentURLs();
    REQUIRE(segmentUTL.size() == 2);

    REQUIRE(segmentUTL[0]->GetIndexRange() == "30-40");
    REQUIRE(segmentUTL[0]->GetIndexURI() == "TestIndex1");
    REQUIRE(segmentUTL[0]->GetMediaRange() == "10-20");
    REQUIRE(segmentUTL[0]->GetMediaURI() == "TestMedia1");

    REQUIRE(segmentUTL[1]->GetIndexRange() == "40-50");
    REQUIRE(segmentUTL[1]->GetIndexURI() == "TestIndex2");
    REQUIRE(segmentUTL[1]->GetMediaRange() == "20-30");
    REQUIRE(segmentUTL[1]->GetMediaURI() == "TestMedia2");
}

/*
 * Test handling headers
 *
 */
TEST_CASE("dash_mpdparser_headers", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     type=\"dynamic\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\""
      "     availabilityStartTime=\"2015-03-24T0:0:0\""
      "     mediaPresentationDuration=\"P0Y0M0DT3H3M30S\">"
      "  <Period id=\"Period0\">"
      "    <AdaptationSet mimeType=\"video/mp4\">"
      "      <Representation id=\"1\" bandwidth=\"250000\">"
      "        <SegmentBase indexRange=\"10-20\">"
      "          <Initialization sourceURL=\"TestSourceUrl\""
      "                          range=\"100-200\">"
      "          </Initialization>"
      "          <RepresentationIndex sourceURL=\"TestSourceIndex\">"
      "          </RepresentationIndex>"
      "        </SegmentBase>"
      "      </Representation></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");
    REQUIRE(mpdTree != nullptr);

    std::vector<dash::mpd::Period*> periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);
    
    dash::mpd::Period* period = periods[0];
    const std::vector<dash::mpd::AdaptationSet*>& adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);
    
    dash::mpd::AdaptationSet* adapt_set = adaptationSets[0];
    auto representation = adaptationSets[0]->GetRepresentation();
    const auto* segmentBase = representation[0]->GetSegmentBase();
    REQUIRE(segmentBase != nullptr);
}

/*
 * Test handling fragments
 *
 */
TEST_CASE("dash_mpdparser_fragments", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
      "<?xml version=\"1.0\"?>"
      "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
      "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\""
      "     availabilityStartTime=\"2015-03-24T0:0:0\""
      "     mediaPresentationDuration=\"P0Y0M0DT3H3M30S\">"
      "  <Period id=\"Period0\" start=\"P0Y0M0DT0H0M10S\">"
      "    <AdaptationSet mimeType=\"video/mp4\">"
      "      <Representation id=\"1\" bandwidth=\"250000\">"
      "      </Representation></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    auto periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);
    
    auto period = periods[0];
    REQUIRE(period != nullptr);

    auto adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    auto adaptationSet = adaptationSets[0];
    REQUIRE(adaptationSet != nullptr);
    REQUIRE(adaptationSet->GetMimeType() == "video/mp4");

    auto representations = adaptationSet->GetRepresentation();
    REQUIRE(representations.size() == 1);

    auto representation = representations[0];
    REQUIRE(representation != nullptr);
    REQUIRE(stoul(representation->GetId()) == 1);
    REQUIRE(representation->GetBandwidth() == 250000);
}

/*
 * Test segment timeline
 *
 */
TEST_CASE("dash_mpdparser_segment_timeline", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml =
        "<?xml version=\"1.0\"?>"
        "<MPD xmlns=\"urn:mpeg:dash:schema:mpd:2011\""
        "     profiles=\"urn:mpeg:dash:profile:isoff-main:2011\""
        "     availabilityStartTime=\"2015-03-24T0:0:0\""
        "     mediaPresentationDuration=\"P0Y0M0DT3H3M30S\">"
        "  <Period start=\"P0Y0M0DT0H0M10S\">"
        "    <AdaptationSet mimeType=\"video/mp4\">"
        "      <SegmentList>"
        "        <SegmentTimeline>"
        "          <S t=\"10\"  d=\"20\" r=\"30\"></S>"
        "        </SegmentTimeline>"
        "      </SegmentList>"
        "      <Representation id=\"1\" bandwidth=\"250000\">"
        "        <SegmentList>"
        "          <SegmentTimeline>"
        "            <S t=\"3\"  d=\"2\" r=\"1\"></S>"
        "            <S t=\"10\" d=\"3\" r=\"0\"></S>"
        "          </SegmentTimeline>"
        "          <SegmentURL media=\"TestMedia0\""
        "                      index=\"TestIndex0\">"
        "          </SegmentURL>"
        "          <SegmentURL media=\"TestMedia1\""
        "                      index=\"TestIndex1\">"
        "          </SegmentURL>"
        "        </SegmentList>"
        "      </Representation></AdaptationSet></Period></MPD>";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree != nullptr);

    auto periods = mpdTree->GetPeriods();
    REQUIRE(periods.size() == 1);

    auto period = periods[0];
    auto adaptationSets = period->GetAdaptationSets();
    REQUIRE(adaptationSets.size() == 1);

    auto adaptationSet = adaptationSets[0];
    auto segmentList = adaptationSet->GetSegmentList();
    REQUIRE(segmentList != nullptr);

    auto segmentTimeline = segmentList->GetSegmentTimeline();
    REQUIRE(segmentTimeline != nullptr);

    const auto timelines = segmentTimeline->GetTimelines();
    REQUIRE(timelines.size() == 1);

    // The first <S> element from SegmentTimeline (from AdaptationSet level)
    REQUIRE(timelines[0]->GetStartTime() == 10);
    REQUIRE(timelines[0]->GetDuration() == 20);
    REQUIRE(timelines[0]->GetRepeatCount() == 30);

    // Checking the Representation
    auto representations = adaptationSet->GetRepresentation();
    REQUIRE(representations.size() == 1);
    auto representation = representations[0];

    segmentList = representation->GetSegmentList();
    REQUIRE(segmentList != nullptr);

    segmentTimeline = segmentList->GetSegmentTimeline();
    REQUIRE(segmentTimeline != nullptr);

    // Check the two <S> elements from SegmentTimeline (from Representation level)
    const auto representationTimelines = segmentTimeline->GetTimelines();
    REQUIRE(representationTimelines.size() == 2);

    REQUIRE(representationTimelines[0]->GetStartTime() == 3);
    REQUIRE(representationTimelines[0]->GetDuration() == 2);
    REQUIRE(representationTimelines[0]->GetRepeatCount() == 1);

    REQUIRE(representationTimelines[1]->GetStartTime() == 10);
    REQUIRE(representationTimelines[1]->GetDuration() == 3);
    REQUIRE(representationTimelines[1]->GetRepeatCount() == 0);
}

/*
 * Test parsing empty xml string
 */
TEST_CASE("dash_mpdparser_missing_xml", "[dash_mpd_parser]") {
    dash::mpd::DASHParser dash_parser;
    std::unique_ptr<dash::mpd::MPD> mpdTree;

    std::string xml = "";

    mpdTree = dash_parser.Parse(xml.data(), xml.length(), "");

    REQUIRE(mpdTree == nullptr);
}

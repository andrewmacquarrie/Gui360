/*
Code is released under Simplified BSD License.
-------------------------------------------------------------------------------
Copyright 2014 Nghia Ho. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this list of
      conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice, this list
      of conditions and the following disclaimer in the documentation and/or other materials
      provided with the distribution.

THIS SOFTWARE IS PROVIDED BY NGHIA HO ``AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL NGHIA HO OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those of the
authors and should not be interpreted as representing official policies, either expressed
or implied, of Nghia Ho.
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <cassert>
#include <vector>

#include "maxflow/graph.h"

using namespace std;
using namespace cv;

typedef Graph<int,int,int> GraphType;

int cutImages(Mat A, Mat B);
GraphType buildGraph(Mat A, Mat B);
void buildImages(Mat A, Mat B, int overlap_width, int cutSize, int xoffset, Mat leftmostSection, int extraRowsCut, std::string outputFile);

int seamcut(std::string inputFile, std::string outputFile, int cutSize, int overlap, int leeway)
{
    Mat A = imread(inputFile);
    assert(A.data);

    int minFlow = 1000000; // some high number. This is bad programming, should set to first flow or look for better structure
    int minFlowIndex = 0;

    for(int i=0; i < leeway; i++) {
        Mat roiLeft(A, Rect(0, 0, overlap, A.rows));
        Mat left = roiLeft.clone();

        int offset = A.cols - overlap - cutSize - i;
        Mat roiRight(A, Rect(offset, 0, overlap, A.rows));
        Mat right = roiRight.clone();

        int curFlow = cutImages(right, left); // content from left of image should br on right of cut as wraps around
        if(curFlow < minFlow) {
            minFlow = curFlow;
            minFlowIndex = i;
            cout << "Adding: Minflow from index " << minFlowIndex << " with flow " << minFlow << endl;
        }


        //imshow("left"+ std::to_string(i), left);
        //imshow("right"+ std::to_string(i), right);
    }

    cout << "Minflow from index " << minFlowIndex << " with flow " << minFlow << endl;
    // CP from above
    Mat roiLeft(A, Rect(0, 0, overlap, A.rows));
    Mat left = roiLeft.clone();
    int offset = A.cols - overlap - cutSize - minFlowIndex;
    Mat roiRight(A, Rect(offset, 0, overlap, A.rows));
    Mat right = roiRight.clone();
    buildImages(right, left, overlap, cutSize, 0, A, minFlowIndex, outputFile); // content from left should be on the right in final image

    return 0;
}

int cutImages(Mat A, Mat B) {
    assert(A.rows == B.rows);

    GraphType g = buildGraph(A, B);

    int flow = g.maxflow();
    cout << "max flow: " << flow << endl;
    return flow;
}

void buildImages(Mat A, Mat B, int overlap_width, int cutSize, int xoffset, Mat leftmostSection, int extraRowsCut, std::string outputFile) {
    GraphType g = buildGraph(A, B);

    Mat graphcut;
    Mat graphcut_and_cutline;

    Mat no_graphcut(A.rows, A.cols, A.type());

    graphcut = no_graphcut.clone();
    graphcut_and_cutline = no_graphcut.clone();

    int idx = 0;
    for(int y=0; y < A.rows; y++) {
        for(int x=0; x < overlap_width; x++) {
            if(g.what_segment(idx) == GraphType::SOURCE) {
                graphcut.at<Vec3b>(y, xoffset + x) = A.at<Vec3b>(y, xoffset + x);
            }
            else {
                graphcut.at<Vec3b>(y, xoffset + x) = B.at<Vec3b>(y, x);
            }

            graphcut_and_cutline.at<Vec3b>(y, xoffset + x) =  graphcut.at<Vec3b>(y, xoffset + x);

            // Draw the cut
            if(x+1 < overlap_width) {
                if(g.what_segment(idx) != g.what_segment(idx+1)) {
                    graphcut_and_cutline.at<Vec3b>(y, xoffset + x) = Vec3b(0,0255,0);
                    graphcut_and_cutline.at<Vec3b>(y, xoffset + x + 1) = Vec3b(0,255,0);
                    graphcut_and_cutline.at<Vec3b>(y, xoffset + x - 1) = Vec3b(0,255,0);
                }
            }

            // Draw the cut
            if(y > 0 && y+1 < A.rows) {
                if(g.what_segment(idx) != g.what_segment(idx + overlap_width)) {
                    graphcut_and_cutline.at<Vec3b>(y-1, xoffset + x) = Vec3b(0,255,0);
                    graphcut_and_cutline.at<Vec3b>(y, xoffset + x) = Vec3b(0,255,0);
                    graphcut_and_cutline.at<Vec3b>(y+1, xoffset + x) = Vec3b(0,255,0);
                }
            }

            idx++;
        }
    }

    Mat finalImage(A.rows, leftmostSection.cols - overlap_width - cutSize - extraRowsCut, A.type());

    Mat wantedAreaOfMain = leftmostSection(Rect(overlap_width,0,leftmostSection.cols - overlap_width - overlap_width - cutSize - extraRowsCut, leftmostSection.rows));

    //imshow("main area", wantedAreaOfMain);
    //waitKey(0);


    wantedAreaOfMain.copyTo(finalImage(Rect(0, 0, wantedAreaOfMain.cols, wantedAreaOfMain.rows)));
    graphcut.copyTo(finalImage(Rect(wantedAreaOfMain.cols, 0, graphcut.cols, graphcut.rows)));

    imwrite(outputFile, finalImage);
}

GraphType buildGraph(Mat A, Mat B) {
    int overlap_width = A.cols;
    int xoffset = 0;

    int est_nodes = A.rows * overlap_width;
    int est_edges = est_nodes * 4;

    GraphType g(est_nodes, est_edges);

    for(int i=0; i < est_nodes; i++) {
        g.add_node();
    }

    // Se   t the source/sink weights
    for(int y=0; y < A.rows; y++) {
        g.add_tweights(y*overlap_width + 0, INT_MAX, 0);
        g.add_tweights(y*overlap_width + overlap_width-1, 0, INT_MAX);
    }

    // Set edge weights
    for(int y=0; y < A.rows; y++) {
        for(int x=0; x < overlap_width; x++) {
            int idx = y*overlap_width + x;

            Vec3b a0 = A.at<Vec3b>(y, xoffset + x);
            Vec3b b0 = B.at<Vec3b>(y, x);
            double cap0 = norm(a0, b0);

            // Add right edge
            if(x+1 < overlap_width) {
                Vec3b a1 = A.at<Vec3b>(y, xoffset + x + 1);
                Vec3b b1 = B.at<Vec3b>(y, x + 1);

                double cap1 = norm(a1, b1);

                g.add_edge(idx, idx + 1, (int)(cap0 + cap1), (int)(cap0 + cap1));
            }

            // Add bottom edge
            if(y+1 < A.rows) {
                Vec3b a2 = A.at<Vec3b>(y+1, xoffset + x);
                Vec3b b2 = B.at<Vec3b>(y+1, x);

                double cap2 = norm(a2, b2);

                g.add_edge(idx, idx + overlap_width, (int)(cap0 + cap2), (int)(cap0 + cap2));
            }
        }
    }
    return g;
}

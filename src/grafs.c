#include "../includes/supportLib.h"
#include "../includes/pbPlots.h"

int CriarGrafico(char* caminhoFicheiro, int *X){
	/* printf("odjaodjaiodjaidjiadjiadjd\n"); */
	/* ScatterPlotSeries series = GetDefaultScatterPlotSeriesSettings();
	series.xs = new double [] {-2, -1, 0, 1, 2};
	series.ys = new double [] {2, -1, -2, -1, 2};
	series.linearInterpolation = true;
	series.lineType = "dashed".toCharArray();
	series.lineThickness = 2d;
	series.color = GetGray(0.3);

	ScatterPlotSettings settings = GetDefaultScatterPlotSettings();
	settings.width = 600;
	settings.height = 400;
	settings.autoBoundaries = true;
	settings.autoPadding = true;
	settings.title = "x^2 - 2".toCharArray();
	settings.xLabel = "X axis".toCharArray();
	settings.yLabel = "Y axis".toCharArray();
	settings.scatterPlotSeries = new ScatterPlotSeries [] {series};

	RGBABitmapImageReference imageReference = CreateRGBABitmapImageReference();
	boolean success;
	StringReference errorMessage = new StringReference();
	success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);
 */
	double *eixoX = (double*)X; 
	double *eixoY = (double*)Y; 
	_Bool success;

	RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
	StringReference *errorMessage = (StringReference *)malloc(sizeof(StringReference));
	success = DrawScatterPlot(canvasReference, 600, 400, eixoX, 5, eixoY, 5, errorMessage);

    if(success){
        size_t length;
        double *pngdata = ConvertToPNG(&length, canvasReference->image);
		/* WriteToFile(pngdata, length, "Historico/Dia 1/imgs/example1.png"); */
        WriteToFile(pngdata, length, caminhoFicheiro);
        DeleteImage(canvasReference->image);
	}else{
	    fprintf(stderr, "Error: ");
	    for(int i = 0; i < (int)errorMessage->stringLength; i++){
            fprintf(stderr, "%c", errorMessage->string[i]);
        }
        fprintf(stderr, "\n");
    }

	return success ? 0 : 1;
}
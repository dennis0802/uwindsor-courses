using System;
using System.Collections.Generic;
using System.Text;

namespace BridgePattern
{
    /* 
     * In summary:
     * Paintings are refined versions of the AbstractPicture, implementing from it
     * Pictures implement the Drawing
     * Specific drawing implementors implement from Drawing (Brush, Can)
     * KEYNOTE: The Drawing is separated from the Picture
     */
    class Bridge
    {
        public Bridge()
        {
            AbstractPicture oil_paint, spray_paint;
            Drawing drawing;
            drawing = new BrushDraw();
            oil_paint = new DrawPicture(drawing);
            Console.Write("For oil painting, ");
            oil_paint.draw();

            drawing = new CanSpray();
            spray_paint = new DrawPicture(drawing);
            Console.Write("For spray painting, ");
            spray_paint.draw();

            Console.ReadKey(true);
        }
    }

    public abstract class AbstractPicture
    {
        abstract public void draw();
        protected Drawing myDrawing;
        public AbstractPicture(Drawing drawing)
        {
            myDrawing = drawing;
        }
        protected void picture_draft() { myDrawing.draft_picture(); }
        protected void picture_color() { myDrawing.color_picture(); }
    }

    public class DrawPicture : AbstractPicture
    {
        public DrawPicture(Drawing drawing) : base(drawing) { }
        public override void draw()
        {
            picture_draft();
            picture_color();
        }
    }

    public abstract class Drawing
    {
        abstract public void draft_picture();
        abstract public void color_picture();
    }

    public class BrushDraw : Drawing
    {
        public override void draft_picture()
        {
            Console.Write("draft with light color ");
        }
        public override void color_picture()
        {
            Console.WriteLine("and color with brushes.");
        }
    }

    public class CanSpray : Drawing
    {
        public override void draft_picture()
        {
            Console.Write("draft with a pencil ");
        }
        public override void color_picture()
        {
            Console.WriteLine("and color with spray cans.");
        }
    }
}

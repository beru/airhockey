
import flash.net.Socket;
import flash.display.MovieClip;

var sock = new Socket();
sock.connect("localhost", 5000);
sock.endian = Endian.LITTLE_ENDIAN;

sock.addEventListener(Event.CONNECT, function(event:Event):void {
	trace("connected");
});

sock.addEventListener(ProgressEvent.SOCKET_DATA, function(event:ProgressEvent):void {
	if (sock.bytesAvailable) {
		var nBytes:int = sock.bytesAvailable;
		var x:Number = sock.readFloat();
		var y:Number = sock.readFloat();
		test.x = x;
		trace(x);
		trace(y);
//		trace(sock.readUTF());
/*
		for (var i:int=0; i<nBytes; ++i) {
			trace(String.fromCharCode(sock.readByte()));
		}
*/
	}
});

test.addEventListener(MouseEvent.CLICK, function(event:MouseEvent):void {
	var s = String(event.stageX) + " " + String(event.stageY);
//	trace(s);
	sock.writeUTF(s);
	sock.flush();
});


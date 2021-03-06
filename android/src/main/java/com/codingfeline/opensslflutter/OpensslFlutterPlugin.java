package com.codingfeline.opensslflutter;

import io.flutter.plugin.common.MethodCall;
import io.flutter.plugin.common.MethodChannel;
import io.flutter.plugin.common.MethodChannel.MethodCallHandler;
import io.flutter.plugin.common.MethodChannel.Result;
import io.flutter.plugin.common.PluginRegistry.Registrar;

/** OpensslFlutterPlugin */
public class OpensslFlutterPlugin implements MethodCallHandler {
  /** Plugin registration. */
  public static void registerWith(Registrar registrar) {
    final MethodChannel channel = new MethodChannel(registrar.messenger(), "openssl_flutter");
    channel.setMethodCallHandler(new OpensslFlutterPlugin());
  }

  @Override
  public void onMethodCall(MethodCall call, Result result) {
    switch (call.method) {
      case "getPlatformVersion":
        result.success("Android " + android.os.Build.VERSION.RELEASE);
        break;
      case "getDigest":
        result.success(getDigest(call.<String>argument("type"), call.<String>argument("message")));
        break;
      default:
        result.notImplemented();
        break;
    }
  }

  public native byte[] getDigest(String digestType, String message);

  static {
    System.loadLibrary("crypto-main");
  }
}

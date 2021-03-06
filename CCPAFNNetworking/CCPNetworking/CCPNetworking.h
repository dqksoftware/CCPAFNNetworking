//
//  CCPNetworking.h
//  CCPNetworkingDemo
//
//  Created by CCP on 16/5/12.
//  Copyright © 2016年 CCP. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Reachability.h"
#import <UIKit/UIKit.h>

/**
 *  手机网络状态
 */
typedef enum{
    
    StatusUnknown           = -1, //未知网络
    StatusNotReachable      = 0,    //没有网络
    StatusReachableViaWWAN  = 1,    //手机自带网络
    StatusReachableViaWiFi  = 2     //wifi
    
}NetworkStatu;

/**
 *  请求方式 GET OR POST
 */
typedef enum HttpMethod {
    GET,
    POST
} httpMethod;


/*
 * DGActivityIndicatorView 动画样式   
 配合该方法使用:
 +(CCPURLSessionTask *)getOrPostWithType:(httpMethod)httpMethod   WithUrl:(NSString *)url params:(NSDictionary *)params animationType:(AnimationType)animationType animationTypeColor:(UIColor *)color isFullScreen:(BOOL)isFull isSecret:(BOOL)isSecret success:(CCPResponseSuccess)success  fail:(CCPResponseFail)fail showHUD:(BOOL)showHUD;
 */
typedef NS_ENUM(NSUInteger, AnimationType) {
    AnimationTypeNineDots,
    AnimationTypeTriplePulse,
    AnimationTypeFiveDots,
    AnimationTypeRotatingSquares,
    AnimationTypeDoubleBounce,
    AnimationTypeTwoDots,
    AnimationTypeThreeDots,
    AnimationTypeBallPulse,
    AnimationTypeBallClipRotate,
    AnimationTypeBallClipRotatePulse,
    AnimationTypeBallClipRotateMultiple,
    AnimationTypeBallRotate,
    AnimationTypeBallZigZag,
    AnimationTypeBallZigZagDeflect,
    AnimationTypeBallTrianglePath,
    AnimationTypeBallScale,
    AnimationTypeLineScale,
    AnimationTypeLineScaleParty,
    AnimationTypeBallScaleMultiple,
    AnimationTypeBallPulseSync,
    AnimationTypeBallBeat,
    AnimationTypeLineScalePulseOut,
    AnimationTypeLineScalePulseOutRapid,
    AnimationTypeBallScaleRipple,
    AnimationTypeBallScaleRippleMultiple,
    AnimationTypeTriangleSkewSpin,
    AnimationTypeBallGridBeat,
    AnimationTypeBallGridPulse,
    AnimationTypeRotatingSandglass,
    AnimationTypeRotatingTrigons,
    AnimationTypeTripleRings,
    AnimationTypeCookieTerminator,
    AnimationTypeBallSpinFadeLoader
};

typedef void( ^ CCPResponseSuccess)(id response);
typedef void( ^ CCPResponseFail)(NSError *error);

typedef void( ^ CCPUploadProgress)(int64_t bytesProgress,
                                  int64_t totalBytesProgress);

typedef void( ^ CCPDownloadProgress)(int64_t bytesProgress,
                                   int64_t totalBytesProgress);

typedef NSURLSessionTask CCPURLSessionTask;

@interface CCPNetworking : NSObject


@property (nonatomic,assign)NetworkStatu networkStats;

/**
 *  单例
 */
+ (CCPNetworking *)sharedCCPNetworking;


/**
 *  开启网络监测
 */
+ (void)startMonitoring;

/**
 *  获取网络状态
 */
+ (NetworkStatu)checkNetStatus;

/**
 *  是否有网络连接
 */

+ (BOOL) isHaveNetwork;

/**
 *  post 或者 get 请求方法,block回调
 *  @param httpMethod       网络请求类型
 *  @param url              请求连接，根路径
 *  @param params           参数字典
 *  @param loadingImageArr  loading图片数组
 *  @param showView         HUD 展示view
 *  @param success          请求成功返回数据
 *  @param fail             请求失败
 *  @param showHUD          是否显示HUD
 */


+(CCPURLSessionTask *)getOrPostWithType:(httpMethod)httpMethod   WithUrl:(NSString *)url params:(NSDictionary *)params loadingImageArr:(NSMutableArray *)loadingImageArr  toShowView:(UIView *)showView isFullScreen:(BOOL)isFull success:(CCPResponseSuccess)success fail:(CCPResponseFail)fail showHUD:(BOOL)showHUD;


/**
 *  post 或者 get 请求方法,block回调 , DGActivityIndicatorView 为指示器
 *  @param httpMethod       网络请求类型
 *  @param url              请求连接，根路径
 *  @param params           参数字典
 *  @param animationType    DGActivityIndicatorView 类型的指示器样式 33种
 *  @param color            指示器颜色
 *  @param isFull           是否覆盖全屏
 *  @param isSecret           是否加密
 *  @param success          请求成功返回数据
 *  @param fail             请求失败
 *  @param showHUD          是否显示HUD
 */

+(CCPURLSessionTask *)getOrPostWithType:(httpMethod)httpMethod   WithUrl:(NSString *)url params:(NSDictionary *)params animationType:(AnimationType)animationType animationTypeColor:(UIColor *)color isFullScreen:(BOOL)isFull success:(CCPResponseSuccess)success  fail:(CCPResponseFail)fail showHUD:(BOOL)showHUD;

/**
 *  上传图片方法 支持多张上传和单张上传
 *  @param image      上传的图片数组
 *  @param url        请求连接，根路径
 *  @param filename   图片的名称(如果不传则以当前时间命名)
 *  @param names      上传图片时参数数组 <后台 处理文件的[字段]>
 *  @param params     参数字典
 *  @param loadingImageArr  loading图片数组
 *  @param showView  HUD 展示view
 *  @param isFull     是否覆盖全屏
 *  @param progress   上传进度
 *  @param success    请求成功返回数据
 *  @param fail       请求失败返回数据
 *  @param showHUD    是否显示HUD
 */

+ (CCPURLSessionTask *)uploadWithImages:(NSArray *)imageArr url:(NSString *)url filename:(NSString *)filename names:(NSArray *)nameArr params:(NSDictionary *)params loadingImageArr:(NSMutableArray *)loadingImageArr toShowView:(UIView *)showView isFullScreen:(BOOL)isFull progress:(CCPUploadProgress)progress success:(CCPResponseSuccess)success fail:(CCPResponseFail)fail showHUD:(BOOL)showHUD;

/**
 *  下载文件方法
 *  @param url           下载地址
 *  @param saveToPath    文件保存的路径,如果不传则保存到Documents目录下，以文件本来的名字命名
 *  loadingImageArr      loading图片数组
 *  @param showView      HUD 展示view
 *  @param isFull        是否覆盖全屏
 *  @param progressBlock 下载进度回调
 *  @param success       下载完成
 *  @param fail          失败
 *  @param showHUD       是否显示HUD
 *  @return              返回请求任务对象，便于操作
 */
+ (CCPURLSessionTask *)downloadWithUrl:(NSString *)url saveToPath:(NSString *)saveToPath loadingImageArr:(NSMutableArray *)loadingImageArr progress:(CCPDownloadProgress )progressBlock toShowView:(UIView *)showView isFullScreen:(BOOL)isFull success:(CCPResponseSuccess )success failure:(CCPResponseFail )fail showHUD:(BOOL)showHUD;

@end

/// Talos Modules
import { Channel } from './channel';
import { Service } from './service';
import { Decorator, Disposable, Inversify } from '@/talos/utilities';

/** Output Channel Contribution. */
@Inversify.injectable()
@Decorator.Class.Rename('Output.Service')
export class Contribution extends Disposable.Registry implements Service {
    //  PROPERTIES  //

    /** Output channel instance. */
    private readonly m_channel: Channel = this.m_subscribe(Channel());

    //  PUBLIC METHODS  //

    /** Gets the underlying channel instance. */
    channel() {
        return this.m_channel;
    }

    /**
     * Handles showing log messages.
     * @param args                  Output arguments.
     */
    log(...args: any[]): void {
        const [message, data] = this.m_format(args);
        this.m_channel.appendLine(message); // should be possible
        if (typeof data !== 'undefined') this.m_channel.appendLine(data);
    }

    /**
     * Handle showing trace messages.
     * @param args                  Output arguments.
     */
    trace(...args: any[]): void {
        this.m_log('trace', args);
    }

    /**
     * Handle showing debug messages.
     * @param args                  Output arguments.
     */
    debug(...args: any[]): void {
        this.m_log('debug', args);
    }

    /**
     * Handle showing info messages.
     * @param args                  Output arguments.
     */
    info(...args: any[]): void {
        this.m_log('info', args);
    }

    /**
     * Handle showing warning messages.
     * @param args                  Output arguments.
     */
    warn(...args: any[]): void {
        this.m_log('warn', args);
    }

    /**
     * Handle showing error messages.
     * @param args                  Output arguments.
     */
    error(...args: any[]): void {
        this.m_log('error', args);
    }

    //  PRIVATE METHODS  //

    /**
     * Handles logging outputs.
     * @param name                  Name of output.
     * @param args                  Output arguments.
     */
    private m_log(name: string, args: any[]) {
        const date = new Date().toISOString();
        const label = name.toUpperCase().padEnd(5);
        const [message, data] = this.m_format(args);

        // attempt writing out final output to be shown
        this.m_channel.appendLine(`${label} (${process.pid}) [${date}] ${message}`);
        if (typeof data !== 'undefined') this.m_channel.appendLine(data);
    }

    /**
     * Handles formatting output arguments.
     * @param args                  Output arguments.
     */
    private m_format(args: any[]): [message: string, data?: string | undefined] {
        // ignore if there is no sized value
        if (args.length === 0) return ['<unknown>'];

        // pull the initial details out now
        const [initial, ...rest] = args;

        const error = initial instanceof Error; // resolve errors
        const message = error ? initial.message : initial.toString();
        return [message as string, error ? initial.stack : rest.toString()];
    }
}

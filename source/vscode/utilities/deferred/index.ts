/// Package Modules
import { Async } from '../async';
import { Inversify } from '../vendors';

/** Deferred Promise Typing. */
@Inversify.injectable()
export class Deferred<T> {
    //  PROPERTIES  //

    /** Encapsulated promise. */
    private readonly m_promise: Promise<T>;

    /** Denotes the current state. */
    private m_state = Async.State.PENDING;

    /** Internal resolution handler. */
    private m_resolve!: (value: T | PromiseLike<T>) => void;

    /** Internal rejection handler. */
    private m_reject!: (reason?: any) => void;

    //  CONSTRUCTORS  //

    /** Constructs a deferred promise. */
    constructor() {
        this.m_promise = new Promise<T>((resolve, reject) => {
            this.m_resolve = resolve;
            this.m_reject = reject;
        });
    }

    //  PUBLIC METHODS  //

    /** Gets the associated promise. */
    promise() {
        return this.m_promise;
    }

    /** Denotes if still pending. */
    pending() {
        return this.m_state === Async.State.PENDING;
    }

    /**
     * Handles resolving the instance.
     * @param value                 Value to resolve.
     */
    resolve(value: T | PromiseLike<T>): Promise<T> {
        if (!this.pending()) return this.m_promise;
        this.m_state = Async.State.RESOLVED; // update now
        return this.m_resolve(value), Promise.resolve(value);
    }

    /**
     * Handles rejecting the instance.
     * @param value                 Reason to reject.
     */
    reject<E>(reason?: E): Promise<T> {
        if (!this.pending()) return this.m_promise;
        this.m_state = Async.State.REJECTED; // update now
        return this.m_reject(reason), Promise.reject(reason);
    }
}
